#pragma once
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QtCore/QProcess>
#include <QtCore/QTimer>
#include <QtWidgets/QListWidget>
#include <QtCore/QPointer>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

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
	0xFFFFFF,
	0xC2C2C2,
	0xC2C2C2,
	0xC2C2C2,
	0xC2C2C2,
	0xD9FF00,
	0x00FF40,
	0x00FFE5,
};

constexpr unsigned int GetStateColor(PAChatClientState state, bool newMessageAvailable, bool force_red)
{
	return state == PAChatClientState_Chatting ? (force_red ? 0xFF5959 : PAChatClientStateColors[state + (int)newMessageAvailable]) : PAChatClientStateColors[state];
}

class PAChatClient : public QObject
{
	Q_OBJECT
private:
	bool searching_;
	bool connected_;
	bool chatting_;
	bool is_typing_;
	bool is_other_typing_;
	int online_count_;

	QPointer<QWebSocket> webSocket_;
	QPointer<QTimer> process_timeout_;
	QPointer<QTimer> pinger_;
	QPointer<QTimer> online_count_update_;
	QPointer<QNetworkAccessManager> netman_;

	QString proxy_host_;
	ushort proxy_port_;

	PAChatClientState state_;

	void StartGeneratingSID();
public:
	PAChatClient(const QString& proxy_host = "", ushort port = 1080, QObject *parent = Q_NULLPTR);
	~PAChatClient();

	bool Search();
	bool Searching();
	bool Connected();
	bool Chatting();
	bool SendMessage(QString messge, int sender_id = 0);
	bool SendTyping(bool typing);
	bool EndChat();
	int OnlineCount();

	void Reconnect();
	PAChatClientState State();
	QString GetProxy();

Q_SIGNALS:
	void onGeneratingSID();
	void onSocketConnecting();
	void onSocketConnected();
	void onChatConnected();
	void onChatSearch();
	void onChatBegin();
	void onChatTyping(bool me, bool typing);
	void onChatMessage(bool me, QString message, int sender_id);
	void onChatImage(bool me, QString image_link, int sender_id);
	void onChatEnd();
	void onChatOnlineCount(int online_count);
	void onSocketDisconnected();
	void onProxyNotWorking();

private Q_SLOTS:
	void onConnected();
	void onDisconnected();
	void onTextMessageReceived(QString message);
	void onPing();
	void onOnlineCountUpdate();
	void onNetworkReply(QNetworkReply* reply);
};
