#include <QtCore/QDebug>
#include <QtCore/QFileInfo>
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>

#include "PAChatClient.h"

QT_USE_NAMESPACE

PAChatClient::PAChatClient(const QString& proxy_host, ushort port, QObject *parent)
	: QObject(parent),
	proxy_host_(proxy_host),
	proxy_port_(port)
{
	connected_ = false;
	searching_ = false;
	chatting_ = false;
	is_typing_ = false;
	is_other_typing_ = false;
	online_count_ = 0;
	process_ = nullptr;

	webSocket_ = new QWebSocket("http://ws.praatanoniem.nl");
	pinger_ = new QTimer(this);
	online_count_update_ = new QTimer(this);

	connect(webSocket_, &QWebSocket::connected, this, &PAChatClient::onConnected);
	connect(webSocket_, &QWebSocket::disconnected, this, &PAChatClient::onDisconnected);
	connect(webSocket_, &QWebSocket::textMessageReceived, this, &PAChatClient::onTextMessageReceived);

	connect(pinger_, &QTimer::timeout, this, &PAChatClient::onPing);
	connect(online_count_update_, &QTimer::timeout, this, &PAChatClient::onOnlineCountUpdate);

	StartGeneratingSID();
}

void PAChatClient::StartGeneratingSID()
{
	if (process_)
	{
		disconnect(process_, 0, 0, 0);
		process_->kill();
		process_->close();
		delete process_;
	}

	process_ = new QProcess(this);

	connect(process_, &QProcess::readyReadStandardOutput, this, &PAChatClient::onProcessInput);
	connect(process_, &QProcess::readyReadStandardError, this, &PAChatClient::onProcessInput);

	QDir dir = QFileInfo(QCoreApplication::applicationFilePath()).absoluteDir();

	process_->setProcessChannelMode(QProcess::MergedChannels);
	process_->setWorkingDirectory(dir.absolutePath());

	if (proxy_host_.length())
	{
		process_->start(dir.absolutePath() + "/sid_alive.exe -t socks5 -h " + proxy_host_ + ":" + QString::number(proxy_port_));
	}
	else
	{
		process_->start(dir.absolutePath() + "/sid_alive.exe");
	}

	state_ = PAChatClientState_GeneratingSID;
	emit onGeneratingSID();
}

void PAChatClient::onProcessInput()
{
	bool done = false;

	QString out = process_->readAllStandardOutput();
	QString process_read_buffer_;

	for (int i = 0; i < out.size(); ++i)
	{
		if (out[i] != '\r')
		{
			if (out[i] == '\n')
			{
				done = true;
				break;
			}
			else
			{
				process_read_buffer_.append(out[i]);
			}
		}
	}

	if (done)
	{
		if (process_read_buffer_ != "0" && process_read_buffer_.length() != 0)
		{
			QUrl url("ws://ws.praatanoniem.nl/socket.io/?EIO=3&transport=websocket&sid=" + process_read_buffer_);

			if (proxy_host_.length())
			{
				QNetworkProxy proxy;
				proxy.setHostName(proxy_host_);
				proxy.setPort(proxy_port_);
				proxy.setType(QNetworkProxy::ProxyType::Socks5Proxy);
				webSocket_->setProxy(proxy);
			}

			webSocket_->open(url);

			state_ = PAChatClientState_SocketConnecting;
			emit onSocketConnecting();
		}
		else
		{
			emit onProxyNotWorking();
			onDisconnected();
		}
		process_read_buffer_.clear();
	}
	else
	{
		emit onProcessInputFailed();
	}
}

PAChatClient::~PAChatClient()
{
	disconnect(webSocket_);
	disconnect(process_);
	disconnect(this, 0, 0, 0);
	//webSocket_.disconnect();
	process_->kill();
}

void PAChatClient::onPing()
{
	webSocket_->sendTextMessage(QStringLiteral("2"));
}

void PAChatClient::onOnlineCountUpdate()
{
	webSocket_->sendTextMessage(QStringLiteral("42[\"count\"]"));
}

void PAChatClient::onConnected()
{
	qDebug() << "WebSocket connected";

	webSocket_->sendTextMessage(QStringLiteral("2probe"));

	state_ = PAChatClientState_ChatConnecting;

	emit onSocketConnected();
	//then you'll receive '3probe'
}

void PAChatClient::onDisconnected()
{
	state_ = PAChatClientState_Disconnected;
	connected_ = false;
	searching_ = false;
	chatting_ = false;
	is_typing_ = false;
	is_other_typing_ = false;
	online_count_ = 0;
	pinger_->stop();
	online_count_update_->stop();
	process_->kill();

	emit onSocketDisconnected();

	//Reconnect?
	StartGeneratingSID();
}

void PAChatClient::onTextMessageReceived(QString incomming_message)
{
	qDebug() << "Message received:" << incomming_message;
	QString json = "";
	if (incomming_message.startsWith("42["))
	{
		incomming_message = incomming_message.mid(2);
		int start_brace = incomming_message.indexOf("\",{");
		if (start_brace != -1)
		{
			start_brace += 2;
			if (incomming_message.indexOf("}]", start_brace) != -1)
			{
				json = incomming_message.mid(start_brace, incomming_message.length() - (start_brace + 1));
			}
		}
	}

	if (json.length() == 0)
	{
		if (searching_ && incomming_message == "[\"start\"]")
		{
			searching_ = false;
			chatting_ = true;
			is_typing_ = false;
			is_other_typing_ = false;

			state_ = PAChatClientState_Chatting;
			//OnChatBegin
			emit onChatBegin();
		}
		else if (chatting_ && incomming_message == "[\"end\"]")
		{
			searching_ = false;
			chatting_ = false;
			is_typing_ = false;
			is_other_typing_ = false;

			state_ = PAChatClientState_Idle;
			//OnChatEnd
			emit onChatEnd();
		}
		else if (!connected_ && incomming_message == "3probe")
		{
			webSocket_->sendTextMessage(QStringLiteral("5"));

			pinger_->start(26000);
			online_count_update_->start(10000);

			connected_ = true;

			state_ = PAChatClientState_Idle;
			//OnConnected
			emit onChatConnected();
		}
	}
	else if (json.length() > 2)
	{
		switch (json.at(2).toLatin1())
		{
		case 't': //{"is_typing_":true}
			{
				bool temp = json[json.length() - 3] == 'u';
				if (temp != is_other_typing_)
				{
					is_other_typing_ = temp;
					//OtherIsTyping
					emit onChatTyping(false, is_other_typing_);
				}
			}
			break;
		case 'u': //{"userCount":123}
			{
				int integer_start = json.indexOf(':') + 1;
				QString num = json.mid(integer_start, json.length() - (integer_start + 1));
				bool ok;
				int temp_val = num.toInt(&ok);
				if (ok)
				{
					online_count_ = temp_val;
					emit onChatOnlineCount(online_count_);
				}
			}
			break;
		case 'm': //{"message":"hello world!","sender":"Onbekende"}
			{
				int start_message = json.indexOf("e\":\"") + 4;
				int end_message = json.lastIndexOf("\",\"s");

				QString recvd_message = json.mid(start_message, end_message - start_message);

				//OnChatMessage
				emit onChatMessage(false, recvd_message, -1);
			}
			break;
		}
	}
}

bool PAChatClient::Search()
{
	if (!connected_ || searching_ || chatting_)
	{
		return false;
	}

	searching_ = true;
	webSocket_->sendTextMessage(QStringLiteral("42[\"start\"]"));
	state_ = PAChatClientState_Searching;
	emit onChatSearch();

	return true;
}

bool PAChatClient::Searching()
{
	return searching_;
}

bool PAChatClient::Connected()
{
	return connected_;
}

bool PAChatClient::Chatting()
{
	return chatting_;
}

bool PAChatClient::SendMessage(QString message, int sender_id)
{
	if (!connected_ || searching_ || !chatting_)
	{
		return false;
	}

	QString format("42[\"message\",{\"message\":\"%1\"}]");

	webSocket_->sendTextMessage(format.arg(message.replace("\"", "\\\"").replace("\\", "\\\\")));

	emit onChatMessage(true, message, sender_id);

	SendTyping(false);

	return true;
}

int PAChatClient::OnlineCount()
{
	return online_count_;
}

PAChatClientState PAChatClient::State()
{
	return state_;
}

bool PAChatClient::SendTyping(bool typing)
{
	if (!connected_ || searching_ || !chatting_ || typing == is_typing_)
	{
		return false;
	}

	is_typing_ = typing;

	webSocket_->sendTextMessage("42[\"typing\",{\"typing\":" + QString(is_typing_ ? "true" : "false") +"}]");
	emit onChatTyping(true, is_typing_);

	return true;
}

bool PAChatClient::EndChat()
{
	if (!connected_ || searching_ || !chatting_)
	{
		return false;
	}

	searching_ = false;
	chatting_ = false;
	is_typing_ = false;
	is_other_typing_ = false;

	state_ = PAChatClientState_Idle;

	webSocket_->sendTextMessage("42[\"end\"]");
	emit onChatEnd();

	return true;	
}

//doesn't work...
void PAChatClient::Reconnect()
{
	webSocket_->disconnect();

	state_ = PAChatClientState_Disconnected;
	connected_ = false;
	searching_ = false;
	chatting_ = false;
	is_typing_ = false;
	is_other_typing_ = false;
	online_count_ = 0;
	pinger_->stop();
	online_count_update_->stop();
	process_->kill();

	connected_ = false;
	searching_ = false;
	chatting_ = false;
	is_typing_ = false;
	is_other_typing_ = false;
	online_count_ = 0;

	StartGeneratingSID();
}