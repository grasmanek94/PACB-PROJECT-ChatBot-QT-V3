#include "PAChatClientGlue.h"
#include "PAChatGlobalId.h"

PAChatClientGlue::PAChatClientGlue(ProxyEntry* proxy, QTabWidget* tabs_container, QCheckBox* send_intro_message_check_box, QCheckBox* story_mode_check_box, QObject *parent)
	: QObject(parent), proxy_(proxy), tabs_container_(tabs_container), force_red(false), send_intro_message_check_box_(send_intro_message_check_box), story_mode_check_box_(story_mode_check_box)
{
	proxy_->PushUseCount();

	client = new PAChatClient(proxy_->GetHost(), proxy_->GetPort(), this);

	connect(client, &PAChatClient::onSocketConnected, this, &PAChatClientGlue::onSocketConnected);
	connect(client, &PAChatClient::onChatConnected, this, &PAChatClientGlue::onChatConnected);
	connect(client, &PAChatClient::onChatSearch, this, &PAChatClientGlue::onChatSearch);
	connect(client, &PAChatClient::onChatBegin, this, &PAChatClientGlue::onChatBegin);
	connect(client, &PAChatClient::onChatTyping, this, &PAChatClientGlue::onChatTyping);
	connect(client, &PAChatClient::onChatMessage, this, &PAChatClientGlue::onChatMessage);
	connect(client, &PAChatClient::onChatEnd, this, &PAChatClientGlue::onChatEnd);
	connect(client, &PAChatClient::onChatOnlineCount, this, &PAChatClientGlue::onChatOnlineCount);
	connect(client, &PAChatClient::onSocketDisconnected, this, &PAChatClientGlue::onSocketDisconnected);

	ui = new PAChatClientUI(tabs_container_, this);

	connect(ui, &PAChatClientUI::onRequestRemoveBot, this, &PAChatClientGlue::onRequestRemoveBot);
	connect(ui, &PAChatClientUI::onRequestChatSendMessage, this, &PAChatClientGlue::onRequestChatSendMessage);
	connect(ui, &PAChatClientUI::onRequestChatEnd, this, &PAChatClientGlue::onRequestChatEnd);
	connect(ui, &PAChatClientUI::onRequestChatKeep, this, &PAChatClientGlue::onRequestChatKeep);
	connect(ui, &PAChatClientUI::onRequestStopAutoSender, this, &PAChatClientGlue::onRequestStopAutoSender);
	connect(ui, &PAChatClientUI::onTextInputChanged, this, &PAChatClientGlue::onTextInputChanged);
	
	auto_sender = new PAChatClientAutoSender(this);
	message_filter = new PAChatClientFilter(this);

	connect(&silence_timer, &QTimer::timeout, this, &PAChatClientGlue::onSilenceTimerHit);
	connect(auto_sender, &PAChatClientAutoSender::onRequestNewMessage, this, &PAChatClientGlue::onAutoSenderMessage);

	int_id_ = PAChatGlobalId::Get();
	string_id_ = "(" + QString::number(int_id_) + ") ";

	QListWidgetItem::setText(string_id_ + "New Bot: Connecting Socket");
	SetStateColor();
}

void PAChatClientGlue::SetStateColor(bool newmessage)
{
	QListWidgetItem::setBackgroundColor(QColor::fromRgb(GetStateColor(client->State(), newmessage, force_red)));
}

PAChatClientGlue::~PAChatClientGlue()
{
	if (proxy_)
	{
		proxy_->PopUseCount();
	}
}

void PAChatClientGlue::onSocketConnected()
{
	QListWidgetItem::setText(string_id_ + "New Bot: Opening Chat");
	SetStateColor();

	emit onGlueSocketConnected();
}

void PAChatClientGlue::onChatConnected()
{
	QListWidgetItem::setText(string_id_ + "Idle: Ready to chat");
	SetStateColor();

	emit onGlueChatConnected();
}

void PAChatClientGlue::onChatSearch()
{
	QListWidgetItem::setText(string_id_ + "Searching");
	SetStateColor();

	emit onGlueChatSearch();
}

void PAChatClientGlue::onChatBegin()
{
	other_message_count_ = 0;
	force_red = false;
	silence_timer.start(300000);
	QListWidgetItem::setText(string_id_ + "Chatting: No Unread Messages");
	SetStateColor();

	ui->RemoveMessages();

	if (send_intro_message_check_box_->checkState())
	{
		client->SendTyping(true);
		client->SendMessage(auto_sender->GetIntroMessage());
	}

	if (story_mode_check_box_->checkState())
	{
		client->SendTyping(true);
		auto_sender->Start();
	}

	emit onGlueChatBegin();
}

bool PAChatClientGlue::ReadyForSearch()
{
	return client->State() == PAChatClientState_Idle;
}

bool PAChatClientGlue::Search()
{
	return client->Search();
}

void PAChatClientGlue::onChatTyping(bool me, bool typing)
{

}

void PAChatClientGlue::onChatMessage(bool me, QString message)
{
	if (!me)
	{
		++other_message_count_;
		QListWidgetItem::setText(string_id_ + "Chatting: Received '" + message + "'");	
		if (!force_red && other_message_count_ < 5)
		{
			force_red = message_filter->IsMessageFiltered(message);
		}
	}

	silence_timer.setInterval(300000);
	SetStateColor(!me);
	ui->AddMessage(me, message);
}

void PAChatClientGlue::onChatEnd()
{
	auto_sender->Stop();
	silence_timer.stop();
	QListWidgetItem::setText(string_id_ + "Idle: Chat ended, ready for new chat");
	SetStateColor();

	emit onGlueChatEnd();
}

void PAChatClientGlue::onChatOnlineCount(int online_count)
{
	emit onOnlineCountUpdate(online_count);
}

void PAChatClientGlue::onTextInputChanged(QString text)
{
	client->SendTyping(text.size() > 0);
}

void PAChatClientGlue::onSocketDisconnected()
{
	QListWidgetItem::setText(string_id_ + "~");
	SetStateColor();

	emit onGlueSocketDisconnected();
}

void PAChatClientGlue::onRequestRemoveBot()
{
	emit onRequestRemove();
}

void PAChatClientGlue::onRequestChatSendMessage(QString message)
{
	if (client->Chatting())
	{
		ui->ClearMessageInput();
		client->SendMessage(message);
	}
}

void PAChatClientGlue::onRequestChatEnd()
{
	if (client->Chatting())
	{
		client->EndChat();
	}
}

void PAChatClientGlue::onRequestChatKeep()
{
	silence_timer.stop();
}

QWidget* PAChatClientGlue::GetTab()
{
	return ui->GetTab();
}

void PAChatClientGlue::FocusInputText()
{
	ui->FocusInputText();
}

void PAChatClientGlue::onSilenceTimerHit()
{
	onRequestChatEnd();
}

void PAChatClientGlue::onRequestStopAutoSender()
{
	auto_sender->Stop();
}

void PAChatClientGlue::onAutoSenderMessage(QString string, bool last_message)
{
	client->SendMessage(string);
	client->SendTyping(!last_message);
}

void PAChatClientGlue::SendMessage(QString string)
{
	client->SendMessage(string);
}

void PAChatClientGlue::Reconnect()
{
	auto_sender->Stop();

	//client->Reconnect();
	delete client;

	ui->ClearMessageInput();
	ui->RemoveMessages();

	client = new PAChatClient(proxy_->GetHost(), proxy_->GetPort(), this);

	connect(client, &PAChatClient::onSocketConnected, this, &PAChatClientGlue::onSocketConnected);
	connect(client, &PAChatClient::onChatConnected, this, &PAChatClientGlue::onChatConnected);
	connect(client, &PAChatClient::onChatSearch, this, &PAChatClientGlue::onChatSearch);
	connect(client, &PAChatClient::onChatBegin, this, &PAChatClientGlue::onChatBegin);
	connect(client, &PAChatClient::onChatTyping, this, &PAChatClientGlue::onChatTyping);
	connect(client, &PAChatClient::onChatMessage, this, &PAChatClientGlue::onChatMessage);
	connect(client, &PAChatClient::onChatEnd, this, &PAChatClientGlue::onChatEnd);
	connect(client, &PAChatClient::onChatOnlineCount, this, &PAChatClientGlue::onChatOnlineCount);
	connect(client, &PAChatClient::onSocketDisconnected, this, &PAChatClientGlue::onSocketDisconnected);

	QListWidgetItem::setText(string_id_ + "New Bot: Connecting Socket");
	SetStateColor();
}
