#include <QTextStream>
#include <QFile>
#include "PAChatClientAutoSender.h"

QString introduction_message;
QStringList story_messages;

static void ReadData()
{
	static bool loaded = false;
	if (!loaded)
	{
		loaded = true;

		QFile f1("berichten/introductie.txt");
		QFile f2("berichten/story_mode.txt");

		f1.open(QIODevice::ReadOnly | QIODevice::Text);
		f2.open(QIODevice::ReadOnly | QIODevice::Text);

		QTextStream s1(&f1);
		QTextStream s2(&f2);

		introduction_message = s1.readAll();
		story_messages = s2.readAll().split('\n');
	}
}

PAChatClientAutoSender::PAChatClientAutoSender(QObject *parent)
	: QObject(parent)
{
	ReadData();
	connect(&message_sender_, &QTimer::timeout, this, &PAChatClientAutoSender::processNextMessage);
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
	message_sender_.start(3500);
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
