#include <QTextStream>
#include <QFile>

#include "PAChatClientMacro.h"

QStringList macro_messages;

static void ReadData()
{
	static bool loaded = false;
	if (!loaded)
	{
		loaded = true;

		QFile f1("berichten/info.txt");

		f1.open(QIODevice::ReadOnly | QIODevice::Text);

		QTextStream s1(&f1);

		macro_messages = s1.readAll().split('\n');
	}
}

PAChatClientMacro::PAChatClientMacro()
{
	ReadData();
}

PAChatClientMacro::~PAChatClientMacro()
{

}
