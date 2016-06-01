#include "PAChatClientGlue.h"
#include "PAChatGlobalId.h"
#include "PAChatManager.h"

PAChatClientGlue::PAChatClientGlue(
	ProxyEntry* proxy, 
	QTabWidget* tabs_container, 
	QCheckBox* send_intro_message_check_box,
	QCheckBox* story_mode_check_box, 
	QCheckBox* ai_mode_check_box,
	QCheckBox* filtered_chat_end_mode_check_box,
	PAChatManager* chat_manager,
	QCheckBox* filter_unneeded_chat_entries_check_box,
	QCheckBox* logging_checkbox,
	QObject *parent)
	: QObject(parent), 
	  proxy_(proxy), 
	  tabs_container_(tabs_container), 
	  force_red(false), 
	  send_intro_message_check_box_(send_intro_message_check_box), 
	  story_mode_check_box_(story_mode_check_box),
	  ai_mode_check_box_(ai_mode_check_box),
	  filtered_chat_end_mode_check_box_(filtered_chat_end_mode_check_box),
	  chat_manager_(chat_manager),
	  filter_unneeded_chat_entries_check_box_(filter_unneeded_chat_entries_check_box),
	  logging_checkbox_(logging_checkbox)
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

	int_id_ = PAChatGlobalId::Get();
	string_id_ = "(" + QString::number(int_id_) + ") ";

	ui = new PAChatClientUI(tabs_container_, int_id_, this);

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

	connect(filter_unneeded_chat_entries_check_box_, &QCheckBox::stateChanged, this, &PAChatClientGlue::showInfoStateChanged);

	QListWidgetItem::setText(string_id_ + "New Bot: Created");
	glue_state_ = PAChatClientGlueState_BotCreated;
	SetStateColor();

	chat_logging_ = false;
}

void PAChatClientGlue::SetStateColor()
{
	int checkedState = filter_unneeded_chat_entries_check_box_->checkState();
	if (checkedState == 0)
	{
		QListWidgetItem::setHidden(false);
	}
	else if (checkedState == 2)
	{
		switch (glue_state_)
		{
		case PAChatClientGlueState_BotCreated:
		case PAChatClientGlueState_OpeningChat:
		case PAChatClientGlueState_ReadyToChat:
		case PAChatClientGlueState_ChattingNoUnreadMessages:
		case PAChatClientGlueState_EndedReadyToChat:
		case PAChatClientGlueState_Disconnected:
		case PAChatClientGlueState_GeneratingSID:
		case PAChatClientGlueState_Connecting:
			QListWidgetItem::setHidden(true);
			break;

		case PAChatClientGlueState_Searching:
		case PAChatClientGlueState_ChattingUnreadMessages:
		case PAChatClientGlueState_ChattingResponded:
			QListWidgetItem::setHidden(false);
			break;
		}
	}
	else if (checkedState == 1) // partial
	{
		switch (glue_state_)
		{
		case PAChatClientGlueState_BotCreated:
		case PAChatClientGlueState_OpeningChat:
		case PAChatClientGlueState_ReadyToChat:
		case PAChatClientGlueState_EndedReadyToChat:
		case PAChatClientGlueState_Disconnected:
		case PAChatClientGlueState_Connecting:
			QListWidgetItem::setHidden(true);
			break;

		case PAChatClientGlueState_GeneratingSID:
		case PAChatClientGlueState_ChattingNoUnreadMessages:
		case PAChatClientGlueState_ChattingUnreadMessages:
		case PAChatClientGlueState_ChattingResponded:
		case PAChatClientGlueState_Searching:
			QListWidgetItem::setHidden(false);
			break;
		}
	}

	QListWidgetItem::setBackgroundColor(QColor::fromRgb(GetStateColor(client ? client->State() : PAChatClientState_Disconnected, glue_state_ == PAChatClientGlueState_ChattingUnreadMessages, force_red)));
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
	glue_state_ = PAChatClientGlueState_OpeningChat;
	SetStateColor();

	emit onGlueSocketConnected();
}

void PAChatClientGlue::onChatConnected()
{
	QListWidgetItem::setText(string_id_ + "Idle: Ready to chat");
	glue_state_ = PAChatClientGlueState_ReadyToChat;
	SetStateColor();

	emit onGlueChatConnected();
}

void PAChatClientGlue::onChatSearch()
{
	QListWidgetItem::setText(string_id_ + "Searching");
	glue_state_ = PAChatClientGlueState_Searching;
	SetStateColor();

	emit onGlueChatSearch();
}

void PAChatClientGlue::onChatBegin()
{
	other_message_count_ = 0;
	force_red = false;
	silence_timer.start(300000);
	QListWidgetItem::setText(string_id_ + "Chatting: No Unread Messages");
	glue_state_ = PAChatClientGlueState_ChattingNoUnreadMessages;
	SetStateColor();

	chat_logging_ = logging_checkbox_->checkState() == 2;

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
				enable_ai = false;
				message_ai->Stop();
				break;
			case 2:
				enable_ai = true;
				enable_auto_sender = false;
				auto_sender->Stop();
				break;
			case 1:
				switcher = !switcher;
				enable_auto_sender = switcher;
				enable_ai = !switcher;
				if (enable_auto_sender)
				{
					message_ai->Stop();
				}
				else if(enable_ai)
				{
					auto_sender->Stop();
				}
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
				client->SendMessage(auto_sender->GetIntroMessage(), 1);
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
		QListWidgetItem::setText(string_id_ + "Chatting: Received '" + message + "'");	
		glue_state_ = PAChatClientGlueState_ChattingUnreadMessages;
		if (message_ai && !message_ai->Stopped())
		{
			message_ai->ProcessMessage(message);
		}

		if (message_filter && !force_red && other_message_count_ < 5)
		{
			force_red = message_filter->IsMessageFiltered(message);
		}

		if (auto_sender && !auto_sender->Stopped() && message.length() > 0)
		{
			if (message[0] == '#')
			{
				QString lower_msg = message.toLower();
				if (lower_msg.length() == 5 && lower_msg == "#stop")
				{
					auto_sender->Stop();
					client->SendMessage("Automatische berichten zijn uitgezet, wat nu?", 1);
				}
			}

			//DBG
			/*if (message.indexOf("!c-445!") != -1)
			{
				__debugbreak();
				qDebug() << "Breakpoint Start Here! ";
				switch (message.length())
				{
				case 1:
					qDebug() << "<" << message[0].unicode() << ">";
					break;
				case 2:
					qDebug() << "<" << message[0].unicode() << ":" << message[1].unicode() << ">";
					break;
				default:
					qDebug() << "<" << message[0].unicode() << ":" << message[1].unicode() << ":" << message[2].unicode() << ">";
					break;
				}
				qDebug() << " Breakpoint End Here!";
			}*/
		}
	}

	if (silence_timer.isActive())
	{
		silence_timer.stop();
		silence_timer.start(300000);
	}

	switch(sender_id)
	{
		case 0:
			if (me)
			{
				glue_state_ = PAChatClientGlueState_ChattingResponded;
			}
			break;

		case 1: // AutoMessage
			break;

		default:
			break;
	}

	SetStateColor();

	if (!me && force_red && filtered_chat_end_mode_check_box_->checkState() > 0)
	{
		if (filtered_chat_end_mode_check_box_->checkState() == 2 || (filtered_chat_end_mode_check_box_->checkState() == 1 && chat_manager_->GetReadyToSearchSize() == 0))
		{
			onRequestChatEnd();
		}
	}
}

void PAChatClientGlue::onChatEnd()
{
	if (auto_sender)
	{
		auto_sender->Stop();
	}
	if (message_ai)
	{
		message_ai->Stop();
	}

	silence_timer.stop();
	QListWidgetItem::setText(string_id_ + "Idle: Chat ended, ready for new chat");
	glue_state_ = PAChatClientGlueState_EndedReadyToChat;
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
	glue_state_ = PAChatClientGlueState_Disconnected;
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
	if (auto_sender)
	{
		auto_sender->Stop();
	}
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
	if (auto_sender)
	{
		auto_sender->Stop();
	}
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

	QListWidgetItem::setText(string_id_ + "New Bot: Created");
	glue_state_ = PAChatClientGlueState_BotCreated;
	SetStateColor();
}

PAChatClientGlue::PAChatClientGlueState PAChatClientGlue::GetGlueState()
{
	return glue_state_;
}

void PAChatClientGlue::onGeneratingSID()
{
	QListWidgetItem::setText(string_id_ + "New Bot: Generating SID (" + client->GetProxy() + ")");
	glue_state_ = PAChatClientGlueState_GeneratingSID;
	SetStateColor();
}

void PAChatClientGlue::onSocketConnecting()
{
	QListWidgetItem::setText(string_id_ + "New Bot: Opening Socket");
	glue_state_ = PAChatClientGlueState_Connecting;
	SetStateColor();
}

void PAChatClientGlue::showInfoStateChanged(int state)
{
	SetStateColor();
}