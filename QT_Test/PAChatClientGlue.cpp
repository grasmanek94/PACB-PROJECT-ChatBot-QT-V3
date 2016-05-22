#include "PAChatClientGlue.h"
#include "PAChatGlobalId.h"

PAChatClientGlue::PAChatClientGlue(
	ProxyEntry* proxy, 
	QTabWidget* tabs_container, 
	QCheckBox* send_intro_message_check_box,
	QCheckBox* story_mode_check_box, 
	QCheckBox* ai_mode_check_box,
	QCheckBox* filtered_chat_end_mode_check_box,
	QObject *parent)
	: QObject(parent), 
	  proxy_(proxy), 
	  tabs_container_(tabs_container), 
	  force_red(false), 
	  send_intro_message_check_box_(send_intro_message_check_box), 
	  story_mode_check_box_(story_mode_check_box),
	  ai_mode_check_box_(ai_mode_check_box),
	  filtered_chat_end_mode_check_box_(filtered_chat_end_mode_check_box)
{
	if (proxy_)
	{
		proxy_->PushUseCount();
	}

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
	connect(client, &PAChatClient::onSocketConnecting, this, &PAChatClientGlue::onSocketConnecting);
	connect(client, &PAChatClient::onGeneratingSID, this, &PAChatClientGlue::onGeneratingSID);
	connect(client, &PAChatClient::onProcessInputFailed, this, &PAChatClientGlue::onProcessInputFailed);

	ui = new PAChatClientUI(tabs_container_, this);

	connect(ui, &PAChatClientUI::onRequestRemoveBot, this, &PAChatClientGlue::onRequestRemoveBot);
	connect(ui, &PAChatClientUI::onRequestChatSendMessage, this, &PAChatClientGlue::onRequestChatSendMessage);
	connect(ui, &PAChatClientUI::onRequestChatEnd, this, &PAChatClientGlue::onRequestChatEnd);
	connect(ui, &PAChatClientUI::onRequestChatKeep, this, &PAChatClientGlue::onRequestChatKeep);
	connect(ui, &PAChatClientUI::onRequestStopAutoSender, this, &PAChatClientGlue::onRequestStopAutoSender);
	connect(ui, &PAChatClientUI::onTextInputChanged, this, &PAChatClientGlue::onTextInputChanged);
	
	auto_sender = new PAChatClientAutoSender(this);
	message_filter = new PAChatClientFilter(this);
	message_ai = new PAChatAI(this);

	connect(&silence_timer, &QTimer::timeout, this, &PAChatClientGlue::onSilenceTimerHit);
	connect(auto_sender, &PAChatClientAutoSender::onRequestNewMessage, this, &PAChatClientGlue::onAutoSenderMessage);
	connect(message_ai, &PAChatAI::onRequestMessage, this, &PAChatClientGlue::onAutoSenderMessage);
	connect(message_ai, &PAChatAI::requestNextChat, this, &PAChatClientGlue::onRequestChatEnd);

	int_id_ = PAChatGlobalId::Get();
	string_id_ = "(" + QString::number(int_id_) + ") ";

	QListWidgetItem::setText(string_id_ + "New Bot: Created");
	SetStateColor();
}

void PAChatClientGlue::SetStateColor(bool newmessage)
{
	QListWidgetItem::setBackgroundColor(QColor::fromRgb(GetStateColor(client ? client->State() : PAChatClientState_Disconnected, newmessage, force_red)));
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

	if (ui)
	{
		ui->RemoveMessages();
	}

	if (client)
	{
		static bool switcher = true;

		int state = ai_mode_check_box_->checkState();
		bool enable_ai = false;
		bool enable_auto_sender = false;

		switch(state)
		{
			case 0:
				enable_auto_sender = true;
				break;
			case 2:
				enable_ai = true;
				break;
			case 1:
				switcher = !switcher;
				enable_auto_sender = switcher;
				enable_ai = !switcher;
				break;
		}

		if (enable_ai && story_mode_check_box_->checkState() && message_ai)
		{
			client->SendTyping(true);
			message_ai->Start();
		}

		if(enable_auto_sender && auto_sender)
		{
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
		}
	}

	emit onGlueChatBegin();
}

bool PAChatClientGlue::ReadyForSearch()
{
	return client && client->State() == PAChatClientState_Idle;
}

bool PAChatClientGlue::Search()
{
	return client && client->Search();
}

void PAChatClientGlue::onChatTyping(bool me, bool typing)
{

}

void PAChatClientGlue::onChatMessage(bool me, QString message, int sender_id)
{
	if (!me)
	{
		++other_message_count_;
	}

	if (ui)
	{
		ui->AddMessage(me, message);
	}

	if (!me)
	{
		// TODO !!!!!!
		QListWidgetItem::setText(string_id_ + "Chatting: Received '" + message + "'");	
		message_ai->ProcessMessage(message);
		if (message_filter && !force_red && other_message_count_ < 5)
		{
			force_red = message_filter->IsMessageFiltered(message);
		}

		if (auto_sender && !auto_sender->Stopped() && message.length() == 5 && message.toLower() == "#stop")
		{
			auto_sender->Stop();
			client->SendMessage("Automatische berichten zijn uitgezet, wat nu?");
		}*/
	}

	if (silence_timer.isActive())
	{
		silence_timer.stop();
		silence_timer.start(300000);
	}

	switch(sender_id)
	{
		case 1: // AutoMessage
			break;
		default:
			SetStateColor(!me);
			break;
	}

}

void PAChatClientGlue::onChatEnd()
{
	/f (auto_sender)
	{
		auto_sender->Stop();
	}
	if (message_ai)
	{
		message_ai->Stop();
	}
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
	if (client)
	{
		client->SendTyping(text.size() > 0);
	}
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
	if (client && client->Chatting())
	{
		if (ui)
		{
			ui->ClearMessageInput();
		}
		client->SendMessage(message);
	}
}

void PAChatClientGlue::onRequestChatEnd()
{
	if (client && client->Chatting())
	{
		ui->ClearMessageInput();
		client->EndChat();
	}
}

void PAChatClientGlue::onRequestChatKeep()
{
	silence_timer.stop();
}

QWidget* PAChatClientGlue::GetTab()
{
	return ui ? ui->GetTab() :nullptr;
}

void PAChatClientGlue::FocusInputText()
{
	if (ui)
	{
		ui->FocusInputText();
	}
}

void PAChatClientGlue::onSilenceTimerHit()
{
	onRequestChatEnd();
}

void PAChatClientGlue::onRequestStopAutoSender()
{
	/*if (auto_sender)
	{
		auto_sender->Stop();
	}*/
	if (message_ai)
	{
		message_ai->Stop();
	}
}

void PAChatClientGlue::onAutoSenderMessage(QString string, bool last_message)
{
	if (client)
	{
		client->SendMessage(string, 1);
		client->SendTyping(!last_message);
	}
}

void PAChatClientGlue::SendMessage(QString string)
{
	if (client)
	{
		client->SendMessage(string);
	}
}

void PAChatClientGlue::Reconnect()
{
	/*if (auto_sender)
	{
		auto_sender->Stop();
	}*/
	if (message_ai)
	{
		message_ai->Stop();
	}

	disconnect(client, 0, 0, 0);
	//client->Reconnect();
	delete client;
	client = nullptr;

	if (ui)
	{
		ui->ClearMessageInput();
		ui->RemoveMessages();
	}

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
	connect(client, &PAChatClient::onSocketConnecting, this, &PAChatClientGlue::onSocketConnecting);
	connect(client, &PAChatClient::onGeneratingSID, this, &PAChatClientGlue::onGeneratingSID);
	connect(client, &PAChatClient::onProcessInputFailed, this, &PAChatClientGlue::onProcessInputFailed);

	QListWidgetItem::setText(string_id_ + "New Bot: Created");
	SetStateColor();
}

void PAChatClientGlue::onProcessInputFailed()
{
	QListWidgetItem::setText(string_id_ + "New Bot: ProcessInput Failed");
	SetStateColor();
}

void PAChatClientGlue::onGeneratingSID()
{
	QListWidgetItem::setText(string_id_ + "New Bot: Generating SID (" + client->GetProxy() + ")");
	SetStateColor();
}

void PAChatClientGlue::onSocketConnecting()
{
	QListWidgetItem::setText(string_id_ + "New Bot: Opening Socket");
	SetStateColor();
}