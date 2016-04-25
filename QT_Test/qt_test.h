#ifndef QT_TEST_H
#define QT_TEST_H

#include <memory>

#include <QtWidgets/QMainWindow>
#include "ui_qt_test.h"
#include "PAChatClient.h"
#include "ProxyList.h"

class QT_Test : public QMainWindow
{
	Q_OBJECT

public:
	QT_Test(QWidget *parent = 0);
	~QT_Test();

private:
	Ui::QT_TestClass ui;
};

#endif // QT_TEST_H
