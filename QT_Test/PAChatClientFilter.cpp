#include <QTextStream>
#include <QFile>
#include "PAChatClientFilter.h"

QStringList disallowed_contents;
QStringList disallowed_begins;

static void ReadData()
{
	static bool loaded = false;
	if (!loaded)
	{
		loaded = true;

		QFile f1("berichten/forbidden_sentences.txt");
		QFile f2("berichten/forbidden_start.txt");

		f1.open(QIODevice::ReadOnly | QIODevice::Text);
		f2.open(QIODevice::ReadOnly | QIODevice::Text);

		QTextStream s1(&f1);
		QTextStream s2(&f2);

		disallowed_contents = s1.readAll().split('\n');
		disallowed_begins = s2.readAll().split('\n');
	}
}

PAChatClientFilter::PAChatClientFilter(QObject *parent)
	: QObject(parent)
{
	ReadData();
}

PAChatClientFilter::~PAChatClientFilter()
{

}

bool PAChatClientFilter::IsMessageFiltered(QString message)
{
	message = message.toLower();

	for (char i = '0'; i <= '9'; ++i)
	{
		message = message.replace(i, '@');
	}

	for (auto& forbidden_content : disallowed_contents)
	{
		if (message.indexOf(forbidden_content) != -1)
		{
			return true;
		}
	}

	for (auto& forbidden_content : disallowed_begins)
	{
		int index = message.indexOf(forbidden_content);
		int maxsize = forbidden_content.indexOf(">");
		for (int i = 0; i < (message.length() <= 3 ? message.length() : 3); ++i)
		{
			if (message[i].isLetterOrNumber())
			{
				if (index == i)
				{
					if (maxsize == -1)
					{
						return true;
					}
					return (message.length() - i) == maxsize;
				}
				return false;
			}
		}
	}

	return false;
}
