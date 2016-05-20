#pragma once
#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtCore/QString>
#include <QtCore/QPointer>

#include "PAChatClientFilter.h"

class PAChatAI : public QObject
{
	Q_OBJECT
private:
	QTimer message_sender_;
	size_t current_index_;
	size_t amount_incomming_messages_;

	QPointer<PAChatClientFilter> filter_;

public:
	PAChatAI(QObject *parent = Q_NULLPTR);
	~PAChatAI();

	void Start();
	void Stop();
	bool Stopped();

	void ProcessMessage(QString message);
Q_SIGNALS:
	void onAnswerMessage(QString input_message, QString answer_message, bool last);
	void requestNextChat();

private Q_SLOTS:
	void processNextMessage();
};
