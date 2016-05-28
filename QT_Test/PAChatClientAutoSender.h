#pragma once
#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtCore/QString>
class PAChatClientAutoSender : public QObject
{
	Q_OBJECT
private:
	QTimer message_sender_;
	size_t current_index_;

public:
	PAChatClientAutoSender(QObject *parent = Q_NULLPTR);
	~PAChatClientAutoSender();

	void Start();
	void Stop();
	bool Stopped();
	QString GetIntroMessage();

Q_SIGNALS:
	void onRequestNewMessage(QString message, bool last);

private Q_SLOTS:
	void processNextMessage();
};

void ReadAutoSenderData(bool reload = false);