#include "qt_test.h"

QT_Test::QT_Test(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//client = std::make_shared<PAChatClient>("", 1080, this);

	QPalette p = ui.chatBoxTexts->palette();

	p.setColor(QPalette::Active, QPalette::Base, Qt::black);
	p.setColor(QPalette::Inactive, QPalette::Base, Qt::black);
	ui.chatBoxTexts->setPalette(p);

	ui.chatBoxTexts->setWordWrapMode(QTextOption::WordWrap);
	ui.chatBoxTexts->setReadOnly(true);
	ui.chatBoxTexts->appendHtml(QString("<div style='background-color:rgb(255,255,255);font-size:14px;color:rgb(10,10,10);'>\
This &copy; is a very long message that will span multiple lines so this should be taken care of well. \
This is a very long message that will span multiple lines so this should be taken care of well. \
This is a very long message that will span multiple lines so this should be taken care of well. \
This is a very long message that will span multiple lines so this should be taken care of well. \
This is a very long message that will span multiple lines so this should be taken care of well. </div>\
<div style='font-size:3px;'>&zwnj;</div>\
<div style='background-color:rgb(249,86,79);font-size:14px;color:rgb(255,255,255);'>\
This &copy; is a very long message that will span multiple lines so this should be taken care of well. \
This is a very long message that will span multiple lines so this should be taken care of well. \
This is a very long message that will span multiple lines so this should be taken care of well. \
This is a very long message that will span multiple lines so this should be taken care of well. \
This is a very long message that will span multiple lines so this should be taken care of well. </div>"));

	QTextCursor c = ui.chatBoxTexts->textCursor();
	c.movePosition(QTextCursor::End);
	ui.chatBoxTexts->setTextCursor(c);

	//proxy_list_ = std::make_shared<ProxyList>(ui.chatProxyList, ui.chatProxyInput, ui.chatProxySubmit, this);
	//ui.chatBoxPeers->addItem()
}

QT_Test::~QT_Test()
{

}
