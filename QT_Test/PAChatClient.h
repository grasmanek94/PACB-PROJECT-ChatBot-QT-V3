#pragma once
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QtCore/QProcess>
#include <QtCore/QTimer>
#include <QListWidget>
#include <array>

enum PAChatClientState
{
	PAChatClientState_Disconnected,//= 0xDEAD
	PAChatClientState_GeneratingSID,
	PAChatClientState_SocketConnecting,
	PAChatClientState_ChatConnecting,
	PAChatClientState_Idle,
	PAChatClientState_Searching,
	PAChatClientState_Chatting
};

const std::array<unsigned int, 8> PAChatClientStateColors
{
	0x000000FF,
	0x222222FF,
	0x444444FF,
	0x666666FF,
	0x00FF6EFF,
	0x00EEFFFF,
	0xFFA200FF,
	0xFF0000FF,
};

constexpr unsigned int GetStateColor(PAChatClientState state, bool newMessageAvailable)
{
	return state == PAChatClientState_Chatting ? PAChatClientStateColors[state + (int)newMessageAvailable] : PAChatClientStateColors[state];
}

class PAChatClient : public QObject, public QListWidgetItem
{
	Q_OBJECT
private:
	bool searching_;
	bool connected_;
	bool chatting_;
	bool is_typing_;
	bool is_other_typing_;
	int online_count_;

	QWebSocket webSocket_;
	QProcess process_;
	QTimer pinger_;
	QTimer online_count_update_;

	QString process_read_buffer_;

	QString proxy_host_;
	ushort proxy_port_;

	PAChatClientState state_;
public:
	PAChatClient(const QString& proxy_host = "", ushort port = 1080, QObject *parent = Q_NULLPTR);
	~PAChatClient();

	bool Search();
	bool Searching();
	bool Connected();
	bool Chatting();
	bool SendMessage(QString messge);
	int OnlineCount();

	PAChatClientState State();

Q_SIGNALS:
	void onSocketConnected();
	void onChatConnected();
	void onChatSearch();
	void onChatBegin();
	void onChatTyping(bool me, bool typing);
	void onChatMessage(bool me, QString message);
	void onChatEnd();
	void onChatOnlineCount(int online_count);
	void onSocketDisconnected();

private Q_SLOTS:
	void onConnected();
	void onDisconnected();
	void onTextMessageReceived(QString message);
	void onPing();
	void onOnlineCountUpdate();
	void onProcessInput();
};
