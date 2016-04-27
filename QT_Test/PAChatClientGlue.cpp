#include "PAChatClientGlue.h"
#include "PAChatGlobalId.h"

PAChatClientGlue::PAChatClientGlue(ProxyEntry* proxy, QTabWidget* tabs_container, QObject *parent)
	: QObject(parent), proxy_(proxy), tabs_container_(tabs_container)
{
	proxy_->PushUseCount();

	client = new PAChatClient(proxy_->GetHost(), proxy_->GetPort(), this);
	ui = new PAChatClientUI(tabs_container_, this);

	connect(client, &PAChatClient::onSocketConnected, this, &PAChatClientGlue::onSocketConnected);
	connect(client, &PAChatClient::onChatConnected, this, &PAChatClientGlue::onChatConnected);
	connect(client, &PAChatClient::onChatSearch, this, &PAChatClientGlue::onChatSearch);
	connect(client, &PAChatClient::onChatBegin, this, &PAChatClientGlue::onChatBegin);
	connect(client, &PAChatClient::onChatTyping, this, &PAChatClientGlue::onChatTyping);
	connect(client, &PAChatClient::onChatMessage, this, &PAChatClientGlue::onChatMessage);
	connect(client, &PAChatClient::onChatEnd, this, &PAChatClientGlue::onChatEnd);
	connect(client, &PAChatClient::onChatOnlineCount, this, &PAChatClientGlue::onChatOnlineCount);
	connect(client, &PAChatClient::onSocketDisconnected, this, &PAChatClientGlue::onSocketDisconnected);

	connect(ui, &PAChatClientUI::onRequestRemoveBot, this, &PAChatClientGlue::onRequestRemoveBot);
	connect(ui, &PAChatClientUI::onRequestChatSendMessage, this, &PAChatClientGlue::onRequestChatSendMessage);
	connect(ui, &PAChatClientUI::onRequestChatEnd, this, &PAChatClientGlue::onRequestChatEnd);
	connect(ui, &PAChatClientUI::onRequestChatKeep, this, &PAChatClientGlue::onRequestChatKeep);
	connect(ui, &PAChatClientUI::onTextInputChanged, this, &PAChatClientGlue::onTextInputChanged);
	
	int_id_ = PAChatGlobalId::Get();
	string_id_ = "(" + QString::number(int_id_) + ") ";

	QListWidgetItem::setText(string_id_ + "New Bot: Connecting Socket");
	SetStateColor();
}

void PAChatClientGlue::SetStateColor(bool newmessage)
{
	QListWidgetItem::setBackgroundColor(QColor::fromRgba(GetStateColor(client->State(), newmessage)));
}

PAChatClientGlue::~PAChatClientGlue()
{
	proxy_->PopUseCount();
}

void PAChatClientGlue::onSocketConnected()
{
	QListWidgetItem::setText(string_id_ + "New Bot: Opening Chat");
	SetStateColor();
}

void PAChatClientGlue::onChatConnected()
{
	QListWidgetItem::setText(string_id_ + "Idle: Ready to chat");
	SetStateColor();
}

void PAChatClientGlue::onChatSearch()
{
	QListWidgetItem::setText(string_id_ + "Searching");
	SetStateColor();
}

void PAChatClientGlue::onChatBegin()
{
	QListWidgetItem::setText(string_id_ + "Chatting: No Unread Messages");
	SetStateColor();

	emit onSearchDone();
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
		QListWidgetItem::setText(string_id_ + "Chatting: Received '" + message + "'");
		SetStateColor(true);
	}
	else
	{
		SetStateColor(false);
	}
}

void PAChatClientGlue::onChatEnd()
{
	QListWidgetItem::setText(string_id_ + "Idle: Chat ended, ready for new chat");
	SetStateColor();
}

void PAChatClientGlue::onChatOnlineCount(int online_count)
{

}

void PAChatClientGlue::onTextInputChanged(QString text)
{
	client->SendTyping(text.size() > 0);
}

void PAChatClientGlue::onSocketDisconnected()
{
	QListWidgetItem::setText(string_id_ + "~");
	SetStateColor();
}

void PAChatClientGlue::onRequestRemoveBot()
{

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

}
