#include <QTextStream>
#include "PAChatClientAutoSender.h"

QString introduction_message = QTextStream("berichten/introductie.txt").readAll();
QStringList story_messages = QTextStream("berichten/story_mode.txt").readAll().split('\n');

PAChatClientAutoSender::PAChatClientAutoSender(QObject *parent)
	: QObject(parent)
{

}

PAChatClientAutoSender::~PAChatClientAutoSender()
{

}

QString PAChatClientAutoSender::GetIntroMessage()
{
	return introduction_message;
}

void PAChatClientAutoSender::Start()
{
	current_index_ = 0;
	message_sender_.start(4000);
}

void PAChatClientAutoSender::Stop()
{
	message_sender_.stop();
}

void PAChatClientAutoSender::processNextMessage()
{
	if (current_index_ < story_messages.size())
	{
		size_t l_index = current_index_++;

		emit onRequestNewMessage(story_messages[l_index], !(current_index_ < story_messages.size()));
	}
	else
	{
		Stop();
	}
}
