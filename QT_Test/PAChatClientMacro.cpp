#include <QtCore/QTextStream>
#include <QtCore/QFile>

#include "PAChatClientMacro.h"

QStringList macro_messages;

static bool ReadData()
{
	static bool loaded = false;
	if (!loaded)
	{
		loaded = true;

		QFile f1("berichten/info.txt");

		f1.open(QIODevice::ReadOnly | QIODevice::Text);

		QTextStream s1(&f1);

		macro_messages = s1.readAll().split('\n');

		return true;
	}
	return false;
}

PAChatClientMacro::PAChatClientMacro(QListWidget* macro_list, QObject *parent)
	: QObject(parent), macro_list_(macro_list)
{
	if (ReadData() && macro_list_)
	{
		for (auto& message : macro_messages)
		{
			macro_list_->addItem(message);
		}
	}

	if (macro_list_)
	{
		connect(macro_list_, &QListWidget::itemDoubleClicked, this, &PAChatClientMacro::onItemDoubleClicked);
	}
}

PAChatClientMacro::~PAChatClientMacro()
{

}

void PAChatClientMacro::onItemDoubleClicked(QListWidgetItem * item)
{
	if (item)
	{
		emit onMacroRequested(item->text());
	}
}