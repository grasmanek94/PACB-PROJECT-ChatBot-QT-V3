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
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QT_TestClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *proxyListContainerGrid;
    QPushButton *chatProxySubmit;
    QLineEdit *chatProxyInput;
    QListWidget *chatProxyList;
    QGridLayout *botListContainerGrid;
    QListWidget *chatBoxPeers;
    QPushButton *chatManagerAddBot;
    QTabWidget *chatBotTabs;
    QWidget *tab;
    QGridLayout *gridLayout_4;
    QGridLayout *chatContainerGrid;
    QHBoxLayout *horizontalLayout;
    QPushButton *chatManagerRemoveBot;
    QPushButton *chatManagerKeepChat;
    QPushButton *chatManagerEndChat;
    QPushButton *pushButton_5;
    QPlainTextEdit *chatBoxTexts;
    QLineEdit *chatBoxMessage;

    void setupUi(QMainWindow *QT_TestClass)
    {
        if (QT_TestClass->objectName().isEmpty())
            QT_TestClass->setObjectName(QStringLiteral("QT_TestClass"));
        QT_TestClass->resize(1010, 300);
        QT_TestClass->setMinimumSize(QSize(1010, 300));
        QIcon icon;
        icon.addFile(QStringLiteral("C:/Users/ChatBot/favicon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        QT_TestClass->setWindowIcon(icon);
        QT_TestClass->setToolButtonStyle(Qt::ToolButtonIconOnly);
        QT_TestClass->setDocumentMode(false);
        QT_TestClass->setTabShape(QTabWidget::Rounded);
        centralWidget = new QWidget(QT_TestClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        proxyListContainerGrid = new QGridLayout();
        proxyListContainerGrid->setSpacing(6);
        proxyListContainerGrid->setObjectName(QStringLiteral("proxyListContainerGrid"));
        proxyListContainerGrid->setSizeConstraint(QLayout::SetMinimumSize);
        chatProxySubmit = new QPushButton(centralWidget);
        chatProxySubmit->setObjectName(QStringLiteral("chatProxySubmit"));
        chatProxySubmit->setMinimumSize(QSize(159, 23));
        chatProxySubmit->setMaximumSize(QSize(159, 16777215));

        proxyListContainerGrid->addWidget(chatProxySubmit, 2, 0, 1, 1);

        chatProxyInput = new QLineEdit(centralWidget);
        chatProxyInput->setObjectName(QStringLiteral("chatProxyInput"));
        chatProxyInput->setMinimumSize(QSize(159, 20));
        chatProxyInput->setMaximumSize(QSize(159, 16777215));

        proxyListContainerGrid->addWidget(chatProxyInput, 1, 0, 1, 1);

        chatProxyList = new QListWidget(centralWidget);
        chatProxyList->setObjectName(QStringLiteral("chatProxyList"));
        chatProxyList->setMinimumSize(QSize(159, 224));
        chatProxyList->setMaximumSize(QSize(159, 16777215));

        proxyListContainerGrid->addWidget(chatProxyList, 0, 0, 1, 1);


        horizontalLayout_2->addLayout(proxyListContainerGrid);

        botListContainerGrid = new QGridLayout();
        botListContainerGrid->setSpacing(6);
        botListContainerGrid->setObjectName(QStringLiteral("botListContainerGrid"));
        botListContainerGrid->setSizeConstraint(QLayout::SetMinimumSize);
        chatBoxPeers = new QListWidget(centralWidget);
        chatBoxPeers->setObjectName(QStringLiteral("chatBoxPeers"));
        chatBoxPeers->setMinimumSize(QSize(289, 250));
        chatBoxPeers->setMaximumSize(QSize(301, 16777215));

        botListContainerGrid->addWidget(chatBoxPeers, 0, 0, 1, 1);

        chatManagerAddBot = new QPushButton(centralWidget);
        chatManagerAddBot->setObjectName(QStringLiteral("chatManagerAddBot"));
        chatManagerAddBot->setMinimumSize(QSize(289, 23));
        chatManagerAddBot->setMaximumSize(QSize(301, 16777215));

        botListContainerGrid->addWidget(chatManagerAddBot, 1, 0, 1, 1);


        horizontalLayout_2->addLayout(botListContainerGrid);

        chatBotTabs = new QTabWidget(centralWidget);
        chatBotTabs->setObjectName(QStringLiteral("chatBotTabs"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(255);
        sizePolicy.setVerticalStretch(255);
        sizePolicy.setHeightForWidth(chatBotTabs->sizePolicy().hasHeightForWidth());
        chatBotTabs->setSizePolicy(sizePolicy);
        chatBotTabs->setMinimumSize(QSize(521, 281));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_4 = new QGridLayout(tab);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        chatContainerGrid = new QGridLayout();
        chatContainerGrid->setSpacing(6);
        chatContainerGrid->setObjectName(QStringLiteral("chatContainerGrid"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        chatManagerRemoveBot = new QPushButton(tab);
        chatManagerRemoveBot->setObjectName(QStringLiteral("chatManagerRemoveBot"));
        chatManagerRemoveBot->setMinimumSize(QSize(119, 23));

        horizontalLayout->addWidget(chatManagerRemoveBot);

        chatManagerKeepChat = new QPushButton(tab);
        chatManagerKeepChat->setObjectName(QStringLiteral("chatManagerKeepChat"));
        chatManagerKeepChat->setMinimumSize(QSize(119, 23));

        horizontalLayout->addWidget(chatManagerKeepChat);

        chatManagerEndChat = new QPushButton(tab);
        chatManagerEndChat->setObjectName(QStringLiteral("chatManagerEndChat"));
        chatManagerEndChat->setMinimumSize(QSize(118, 23));

        horizontalLayout->addWidget(chatManagerEndChat);

        pushButton_5 = new QPushButton(tab);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setMinimumSize(QSize(119, 23));

        horizontalLayout->addWidget(pushButton_5);


        chatContainerGrid->addLayout(horizontalLayout, 3, 0, 1, 1);

        chatBoxTexts = new QPlainTextEdit(tab);
        chatBoxTexts->setObjectName(QStringLiteral("chatBoxTexts"));
        chatBoxTexts->setMinimumSize(QSize(495, 178));

        chatContainerGrid->addWidget(chatBoxTexts, 1, 0, 1, 1);

        chatBoxMessage = new QLineEdit(tab);
        chatBoxMessage->setObjectName(QStringLiteral("chatBoxMessage"));
        chatBoxMessage->setMinimumSize(QSize(495, 20));
        chatBoxMessage->setMaximumSize(QSize(16777215, 16777215));

        chatContainerGrid->addWidget(chatBoxMessage, 2, 0, 1, 1);


        gridLayout_4->addLayout(chatContainerGrid, 0, 0, 1, 1);

        chatBotTabs->addTab(tab, QString());

        horizontalLayout_2->addWidget(chatBotTabs);

        QT_TestClass->setCentralWidget(centralWidget);

        retranslateUi(QT_TestClass);

        chatBotTabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QT_TestClass);
    } // setupUi

    void retranslateUi(QMainWindow *QT_TestClass)
    {
        QT_TestClass->setWindowTitle(QApplication::translate("QT_TestClass", "PA ChatBot", 0));
        chatProxySubmit->setText(QApplication::translate("QT_TestClass", "Add Proxies", 0));
        chatManagerAddBot->setText(QApplication::translate("QT_TestClass", "Add New Bot", 0));
        chatManagerRemoveBot->setText(QApplication::translate("QT_TestClass", "Remove Bot", 0));
        chatManagerKeepChat->setText(QApplication::translate("QT_TestClass", "Keep Chat", 0));
        chatManagerEndChat->setText(QApplication::translate("QT_TestClass", "End Chat", 0));
        pushButton_5->setText(QApplication::translate("QT_TestClass", "Send", 0));
        chatBotTabs->setTabText(chatBotTabs->indexOf(tab), QApplication::translate("QT_TestClass", "Tab 1", 0));
    } // retranslateUi

};

namespace Ui {
    class QT_TestClass: public Ui_QT_TestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_TEST_H
