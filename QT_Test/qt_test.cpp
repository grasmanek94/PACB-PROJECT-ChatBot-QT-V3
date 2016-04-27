#include "qt_test.h"

QT_Test::QT_Test(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	manager = new PAChatManager(ui.chatProxyList, ui.chatProxyInput, ui.chatProxySubmit, ui.chatBoxPeers, ui.chatBotTabs, ui.chatManagerAddBot, ui.chatManagerRequestNewChat, ui.autoSearchCheckBox, this);
}

QT_Test::~QT_Test()
{

}
