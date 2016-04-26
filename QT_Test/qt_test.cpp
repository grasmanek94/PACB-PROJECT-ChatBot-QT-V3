#include "qt_test.h"

#include "PAChatClientUI.h"

PAChatClientUI* uix;
QT_Test::QT_Test(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	uix = new PAChatClientUI(ui.chatBotTabs, this);
}

QT_Test::~QT_Test()
{

}
