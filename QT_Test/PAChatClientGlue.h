#pragma once
#include <QListWidget>

#include <QPointer>

#include "PAChatClient.h"
#include "PAChatClientUI.h"
#include "ProxyEntry.h"

class PAChatClientGlue: public QObject, public QListWidgetItem
{
	Q_OBJECT
private:
	QPointer<PAChatClient> client;
	QPointer<PAChatClientUI> ui;
	QPointer<ProxyEntry> proxy_;
	QPointer<QTabWidget> tabs_container_;

	int int_id_;
	QString string_id_;
public:
	PAChatClientGlue(ProxyEntry* proxy, QTabWidget* tabs_container_, QObject *parent = Q_NULLPTR);
	~PAChatClientGlue();

private:
	void SetStateColor(bool newmessage = false);

public:

	bool ReadyForSearch();
	bool Search();
	
Q_SIGNALS:
	void onSearchDone();

	void onRequestRemove();
	void onOnlineCountUpdate(int online_count);

private Q_SLOTS:
	void onSocketConnected();
	void onChatConnected();
	void onChatSearch();
	void onChatBegin();
	void onChatTyping(bool me, bool typing);
	void onChatMessage(bool me, QString message);
	void onChatEnd();
	void onChatOnlineCount(int online_count);
	void onSocketDisconnected();
	void onRequestRemoveBot();
	void onRequestChatSendMessage(QString message);
	void onRequestChatEnd();
	void onRequestChatKeep();
	void onTextInputChanged(QString text);
};
 