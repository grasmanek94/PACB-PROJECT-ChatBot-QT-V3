#include <QtCore/QTextStream>
#include <QtCore/QFile>
#include <QtCore/QList>
#include <QtCore/QStringList>
#include "PAChatClientAutoSender.h"

QList<QStringList> story_messages;

void ReadAutoSenderData(bool reload)
{
	static bool loaded = false;
	if (!loaded || reload)
	{
		loaded = true;

		QFile f1("berichten/story_mode.txt");

		f1.open(QIODevice::ReadOnly | QIODevice::Text);

		QTextStream s1(&f1);

		QStringList story_messages_premade = s1.readAll().split('\n');
		for (auto &elem : story_messages_premade)
		{
			QStringList list = elem.split(" | ");
			story_messages.append(list);
		}
	}
}

PAChatClientAutoSender::PAChatClientAutoSender(QObject *parent)
	: QObject(parent)
{
	ReadAutoSenderData();
	connect(&message_sender_, &QTimer::timeout, this, &PAChatClientAutoSender::processNextMessage);
}

PAChatClientAutoSender::~PAChatClientAutoSender()
{

}

QString PAChatClientAutoSender::GetIntroMessage()
{
	if (story_messages.size())
	{
		return GetMessage(0);
	}
	return "";
}

void PAChatClientAutoSender::Start(int current_story)
{
	current_story_ = current_story;
	current_index_ = 1;
	message_sender_.start(3500);
}

void PAChatClientAutoSender::Stop()
{
	message_sender_.stop();
}

bool PAChatClientAutoSender::Stopped()
{
	return !message_sender_.isActive();
}

void PAChatClientAutoSender::processNextMessage()
{
	if (current_index_ < story_messages.size())
	{
		size_t l_index = current_index_++;

		emit onRequestNewMessage(GetMessage(l_index), !(current_index_ < story_messages.size()));
	}
	else
	{
		Stop();
	}
}

int PAChatClientAutoSender::GetCurrentStory()
{
	return current_story_;
}

QString PAChatClientAutoSender::GetMessage(size_t index)
{
	if (index >= story_messages.size())
	{
		return "";
	}

	QStringList* list = &story_messages[index];

	if (list->size() == 0)
	{
		return "";
	}

	if (list->size() == 1)
	{
		return list->at(0);
	}

	if (current_story_ != -1 && current_story_ < list->size())
	{
		return list->at(current_story_);	
	}

	return list->at(qrand() % list->size());
}