/********************************************************************************
** Form generated from reading UI file 'qt_test.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_TEST_H
#define UI_QT_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QT_TestClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QPushButton *pushButton_5;
    QPushButton *chatProxySubmit;
    QPlainTextEdit *chatBoxTexts;
    QLineEdit *chatBoxMessage;
    QListWidget *chatProxyList;
    QLineEdit *chatProxyInput;
    QListWidget *chatBoxPeers;

    void setupUi(QMainWindow *QT_TestClass)
    {
        if (QT_TestClass->objectName().isEmpty())
            QT_TestClass->setObjectName(QStringLiteral("QT_TestClass"));
        QT_TestClass->resize(721, 291);
        QIcon icon;
        icon.addFile(QStringLiteral("../../../ChatBot/favicon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        QT_TestClass->setWindowIcon(icon);
        QT_TestClass->setToolButtonStyle(Qt::ToolButtonIconOnly);
        QT_TestClass->setDocumentMode(false);
        QT_TestClass->setTabShape(QTabWidget::Rounded);
        centralWidget = new QWidget(QT_TestClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout->addWidget(pushButton_4);

        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        horizontalLayout->addWidget(pushButton_5);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 1);

        chatProxySubmit = new QPushButton(centralWidget);
        chatProxySubmit->setObjectName(QStringLiteral("chatProxySubmit"));
        chatProxySubmit->setMinimumSize(QSize(152, 0));
        chatProxySubmit->setMaximumSize(QSize(152, 23));

        gridLayout->addWidget(chatProxySubmit, 3, 1, 1, 1);

        chatBoxTexts = new QPlainTextEdit(centralWidget);
        chatBoxTexts->setObjectName(QStringLiteral("chatBoxTexts"));
        chatBoxTexts->setMinimumSize(QSize(401, 213));

        gridLayout->addWidget(chatBoxTexts, 1, 0, 1, 1);

        chatBoxMessage = new QLineEdit(centralWidget);
        chatBoxMessage->setObjectName(QStringLiteral("chatBoxMessage"));
        chatBoxMessage->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(chatBoxMessage, 2, 0, 1, 1);

        chatProxyList = new QListWidget(centralWidget);
        chatProxyList->setObjectName(QStringLiteral("chatProxyList"));
        chatProxyList->setMinimumSize(QSize(152, 213));
        chatProxyList->setMaximumSize(QSize(152, 16777215));

        gridLayout->addWidget(chatProxyList, 1, 1, 1, 1);

        chatProxyInput = new QLineEdit(centralWidget);
        chatProxyInput->setObjectName(QStringLiteral("chatProxyInput"));
        chatProxyInput->setMaximumSize(QSize(152, 16777215));

        gridLayout->addWidget(chatProxyInput, 2, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 1, 1, 1);

        chatBoxPeers = new QListWidget(centralWidget);
        chatBoxPeers->setObjectName(QStringLiteral("chatBoxPeers"));
        chatBoxPeers->setMinimumSize(QSize(136, 273));
        chatBoxPeers->setMaximumSize(QSize(271, 16777215));

        gridLayout_2->addWidget(chatBoxPeers, 0, 0, 1, 1);

        QT_TestClass->setCentralWidget(centralWidget);

        retranslateUi(QT_TestClass);

        QMetaObject::connectSlotsByName(QT_TestClass);
    } // setupUi

    void retranslateUi(QMainWindow *QT_TestClass)
    {
        QT_TestClass->setWindowTitle(QApplication::translate("QT_TestClass", "PA ChatBot", 0));
        pushButton_4->setText(QApplication::translate("QT_TestClass", "PushButton", 0));
        pushButton_3->setText(QApplication::translate("QT_TestClass", "PushButton", 0));
        pushButton_2->setText(QApplication::translate("QT_TestClass", "PushButton", 0));
        pushButton->setText(QApplication::translate("QT_TestClass", "PushButton", 0));
        pushButton_5->setText(QApplication::translate("QT_TestClass", "PushButton", 0));
        chatProxySubmit->setText(QApplication::translate("QT_TestClass", "Add Proxies", 0));
    } // retranslateUi

};

namespace Ui {
    class QT_TestClass: public Ui_QT_TestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_TEST_H
