#pragma once
#include <QObject>
#include <QTimer>
#include <QString>
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
	QString GetIntroMessage();

Q_SIGNALS:
	void onRequestNewMessage(QString message, bool last);

private Q_SLOTS:
	void processNextMessage();
};
