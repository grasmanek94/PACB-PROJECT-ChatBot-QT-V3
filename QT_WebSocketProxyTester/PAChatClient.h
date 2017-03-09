#pragma once
#include <QtCore/QObject>
#include <QtCore/QProcess>
#include <QtCore/QTimer>
#include <QtCore/QPointer>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

#include <array>
#include "ProxyEntry.h"

class PAChatClient : public QObject
{
	Q_OBJECT
private:
	QPointer<QTimer> process_timeout_;
	QPointer<QNetworkAccessManager> netman_;
	QPointer<ProxyEntry> proxy_;
	QPointer<QNetworkReply> reply_manager_;
public:
	PAChatClient(ProxyEntry* proxy, QObject *parent = Q_NULLPTR);
	~PAChatClient();

	ProxyEntry* GetProxy();
Q_SIGNALS:
	void onProxyWorking();
	void onProxyNotWorking();

private Q_SLOTS:
	void onTimeout();
	void onNetworkReply(QNetworkReply* reply);
};
