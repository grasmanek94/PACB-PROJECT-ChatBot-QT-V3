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
	QTimer question_akser_;
	QTimer reaction_sender_;

	enum PAChatAIState
	{
		PAChatAIState_Failed,
		PAChatAIState_AskingQuestion,
		PAChatAIState_WaitingForAnswer,
		PAChatAIState_SendingReaction,
		PAChatAIState_Done
	};

	PAChatAIState state_;
	size_t current_index_;
	size_t amount_incomming_messages_;

	QPointer<PAChatClientFilter> filter_;

	QString GetQuestion(size_t index);
	QString GetReaction(size_t index);

	bool IsPossibleAnswer(size_t index, QString message);
	bool IsGoodAnswer(size_t index, QString message);

	void AskNextQuestion();
	void PushNextReaction();

public:
	PAChatAI(QObject *parent = Q_NULLPTR);
	~PAChatAI();

	void Start();
	void Stop();
	bool Stopped();

	void ProcessMessage(QString message);
Q_SIGNALS:
	void onRequestMessage(QString message);
	void requestNextChat();

private Q_SLOTS:
	void onAskNextQuestion();
	void onReactionToAnswer();
};
