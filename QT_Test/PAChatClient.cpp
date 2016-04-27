#include <QtCore/QDebug>
#include <QtCore/QFileInfo>
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>

#include "PAChatClient.h"

QT_USE_NAMESPACE

PAChatClient::PAChatClient(const QString& proxy_host, ushort port, QObject *parent)
	: QObject(parent),
	webSocket_("http://ws.praatanoniem.nl"),
	pinger_(this),
	online_count_update_(this),
	proxy_host_(proxy_host),
	proxy_port_(port)
{
	connected_ = false;
	searching_ = false;
	chatting_ = false;
	is_typing_ = false;
	is_other_typing_ = false;
	online_count_ = 0;

	connect(&webSocket_, &QWebSocket::connected, this, &PAChatClient::onConnected);
	connect(&webSocket_, &QWebSocket::disconnected, this, &PAChatClient::onDisconnected);

	connect(&pinger_, &QTimer::timeout, this, &PAChatClient::onPing);
	connect(&online_count_update_, &QTimer::timeout, this, &PAChatClient::onOnlineCountUpdate);

	connect(&process_, &QProcess::readyReadStandardOutput, this, &PAChatClient::onProcessInput);  // connect process signals with your code
	connect(&process_, &QProcess::readyReadStandardError, this, &PAChatClient::onProcessInput);  // same here

	QDir dir = QFileInfo(QCoreApplication::applicationFilePath()).absoluteDir();

	process_.setProcessChannelMode(QProcess::MergedChannels);
	process_.setWorkingDirectory(dir.absolutePath());

	if (proxy_host.length())
	{
		process_.start(dir.absolutePath() + "/sid_alive.exe -t socks5 -h " + proxy_host + ":" + QString::number(port));
	}
	else
	{
		process_.start(dir.absolutePath() + "/sid_alive.exe");
	}

	state_ = PAChatClientState_GeneratingSID;
}

void PAChatClient::onProcessInput()
{
	bool done = false;

	QString out = process_.readAllStandardOutput();
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
				webSocket_.setProxy(proxy);
			}

			webSocket_.open(url);

			state_ = PAChatClientState_SocketConnecting;
		}
		else
		{
			onDisconnected();
		}
		process_read_buffer_.clear();
	}
}

PAChatClient::~PAChatClient()
{
	webSocket_.disconnect();
	process_.kill();
}

void PAChatClient::onPing()
{
	webSocket_.sendTextMessage(QStringLiteral("2"));
}

void PAChatClient::onOnlineCountUpdate()
{
	webSocket_.sendTextMessage(QStringLiteral("42[\"count\"]"));
}

void PAChatClient::onConnected()
{
	qDebug() << "WebSocket connected";

	connect(&webSocket_, &QWebSocket::textMessageReceived, this, &PAChatClient::onTextMessageReceived);
	webSocket_.sendTextMessage(QStringLiteral("2probe"));

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
	pinger_.stop();
	online_count_update_.stop();
	process_.kill();
	emit onSocketDisconnected();
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
			webSocket_.sendTextMessage(QStringLiteral("5"));

			pinger_.start(26000);
			online_count_update_.start(10000);

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
				emit onChatMessage(false, recvd_message);
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
	webSocket_.sendTextMessage(QStringLiteral("42[\"start\"]"));
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

bool PAChatClient::SendMessage(QString message)
{
	if (!connected_ || searching_ || !chatting_)
	{
		return false;
	}

	emit onChatMessage(true, message);

	webSocket_.sendTextMessage("42[\"message\"]{\"message\":\"" + message.replace("\"", "\\\"").replace("\\", "\\\\") + "\"}]");
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

	webSocket_.sendTextMessage("42[\"typing\",{\"typing\":" + QString(is_typing_ ? "true" : "false") +"}]");
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

	webSocket_.sendTextMessage("42[\"end\"]");
	emit onChatEnd();

	return true;	
}