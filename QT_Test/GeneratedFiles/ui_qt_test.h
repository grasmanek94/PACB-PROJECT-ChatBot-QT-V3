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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
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
    QLineEdit *chatProxyInput;
    QLabel *onlineCountLabel;
    QListWidget *chatProxyList;
    QPushButton *chatProxySubmit;
    QPushButton *reloadFiltersSubmit;
    QGridLayout *botListContainerGrid;
    QPushButton *chatManagerRequestNewChat;
    QCheckBox *autoSenderState;
    QListWidget *preparedTextsBox;
    QCheckBox *autoAIModeCheckBox;
    QListWidget *chatBoxPeers;
    QCheckBox *autoSearchCheckBox;
    QPushButton *chatManagerFillBots;
    QCheckBox *autoSendIntroductionMessage;
    QPushButton *chatManagerAddBot;
    QHBoxLayout *horizontalLayout;
    QCheckBox *endFilteredChatsState;
    QCheckBox *unneededChatsHiderState;
    QTabWidget *chatBotTabs;

    void setupUi(QMainWindow *QT_TestClass)
    {
        if (QT_TestClass->objectName().isEmpty())
            QT_TestClass->setObjectName(QStringLiteral("QT_TestClass"));
        QT_TestClass->resize(1400, 608);
        QT_TestClass->setMinimumSize(QSize(1400, 400));
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
        chatProxyInput = new QLineEdit(centralWidget);
        chatProxyInput->setObjectName(QStringLiteral("chatProxyInput"));
        chatProxyInput->setMinimumSize(QSize(159, 20));
        chatProxyInput->setMaximumSize(QSize(159, 16777215));

        proxyListContainerGrid->addWidget(chatProxyInput, 2, 0, 1, 1);

        onlineCountLabel = new QLabel(centralWidget);
        onlineCountLabel->setObjectName(QStringLiteral("onlineCountLabel"));

        proxyListContainerGrid->addWidget(onlineCountLabel, 4, 0, 1, 1);

        chatProxyList = new QListWidget(centralWidget);
        chatProxyList->setObjectName(QStringLiteral("chatProxyList"));
        chatProxyList->setMinimumSize(QSize(159, 224));
        chatProxyList->setMaximumSize(QSize(159, 16777215));
        QFont font;
        font.setPointSize(10);
        chatProxyList->setFont(font);

        proxyListContainerGrid->addWidget(chatProxyList, 0, 0, 1, 1);

        chatProxySubmit = new QPushButton(centralWidget);
        chatProxySubmit->setObjectName(QStringLiteral("chatProxySubmit"));
        chatProxySubmit->setMinimumSize(QSize(159, 23));
        chatProxySubmit->setMaximumSize(QSize(159, 16777215));

        proxyListContainerGrid->addWidget(chatProxySubmit, 3, 0, 1, 1);

        reloadFiltersSubmit = new QPushButton(centralWidget);
        reloadFiltersSubmit->setObjectName(QStringLiteral("reloadFiltersSubmit"));

        proxyListContainerGrid->addWidget(reloadFiltersSubmit, 1, 0, 1, 1);


        horizontalLayout_2->addLayout(proxyListContainerGrid);

        botListContainerGrid = new QGridLayout();
        botListContainerGrid->setSpacing(6);
        botListContainerGrid->setObjectName(QStringLiteral("botListContainerGrid"));
        botListContainerGrid->setSizeConstraint(QLayout::SetDefaultConstraint);
        botListContainerGrid->setHorizontalSpacing(6);
        botListContainerGrid->setContentsMargins(-1, 0, -1, 0);
        chatManagerRequestNewChat = new QPushButton(centralWidget);
        chatManagerRequestNewChat->setObjectName(QStringLiteral("chatManagerRequestNewChat"));
        chatManagerRequestNewChat->setMinimumSize(QSize(250, 0));
        chatManagerRequestNewChat->setMaximumSize(QSize(500, 16777215));

        botListContainerGrid->addWidget(chatManagerRequestNewChat, 4, 0, 1, 1);

        autoSenderState = new QCheckBox(centralWidget);
        autoSenderState->setObjectName(QStringLiteral("autoSenderState"));
        autoSenderState->setMinimumSize(QSize(250, 0));
        autoSenderState->setMaximumSize(QSize(250, 16777215));
        autoSenderState->setChecked(true);

        botListContainerGrid->addWidget(autoSenderState, 4, 1, 1, 1);

        preparedTextsBox = new QListWidget(centralWidget);
        preparedTextsBox->setObjectName(QStringLiteral("preparedTextsBox"));
        preparedTextsBox->setMinimumSize(QSize(250, 250));
        preparedTextsBox->setMaximumSize(QSize(250, 16777215));
        preparedTextsBox->setFont(font);

        botListContainerGrid->addWidget(preparedTextsBox, 0, 1, 1, 1);

        autoAIModeCheckBox = new QCheckBox(centralWidget);
        autoAIModeCheckBox->setObjectName(QStringLiteral("autoAIModeCheckBox"));
        autoAIModeCheckBox->setMinimumSize(QSize(250, 0));
        autoAIModeCheckBox->setMaximumSize(QSize(250, 16777215));
        autoAIModeCheckBox->setTristate(true);

        botListContainerGrid->addWidget(autoAIModeCheckBox, 2, 1, 1, 1);

        chatBoxPeers = new QListWidget(centralWidget);
        chatBoxPeers->setObjectName(QStringLiteral("chatBoxPeers"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(chatBoxPeers->sizePolicy().hasHeightForWidth());
        chatBoxPeers->setSizePolicy(sizePolicy);
        chatBoxPeers->setMinimumSize(QSize(400, 250));
        chatBoxPeers->setMaximumSize(QSize(500, 16777215));
        chatBoxPeers->setFont(font);

        botListContainerGrid->addWidget(chatBoxPeers, 0, 0, 1, 1);

        autoSearchCheckBox = new QCheckBox(centralWidget);
        autoSearchCheckBox->setObjectName(QStringLiteral("autoSearchCheckBox"));
        autoSearchCheckBox->setMinimumSize(QSize(250, 0));
        autoSearchCheckBox->setMaximumSize(QSize(250, 16777215));
        autoSearchCheckBox->setChecked(true);

        botListContainerGrid->addWidget(autoSearchCheckBox, 5, 1, 1, 1);

        chatManagerFillBots = new QPushButton(centralWidget);
        chatManagerFillBots->setObjectName(QStringLiteral("chatManagerFillBots"));
        chatManagerFillBots->setMinimumSize(QSize(250, 0));
        chatManagerFillBots->setMaximumSize(QSize(500, 16777215));

        botListContainerGrid->addWidget(chatManagerFillBots, 5, 0, 1, 1);

        autoSendIntroductionMessage = new QCheckBox(centralWidget);
        autoSendIntroductionMessage->setObjectName(QStringLiteral("autoSendIntroductionMessage"));
        autoSendIntroductionMessage->setMinimumSize(QSize(250, 0));
        autoSendIntroductionMessage->setMaximumSize(QSize(250, 16777215));
        autoSendIntroductionMessage->setChecked(true);

        botListContainerGrid->addWidget(autoSendIntroductionMessage, 3, 1, 1, 1);

        chatManagerAddBot = new QPushButton(centralWidget);
        chatManagerAddBot->setObjectName(QStringLiteral("chatManagerAddBot"));
        chatManagerAddBot->setMinimumSize(QSize(250, 0));
        chatManagerAddBot->setMaximumSize(QSize(500, 16777215));

        botListContainerGrid->addWidget(chatManagerAddBot, 3, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        endFilteredChatsState = new QCheckBox(centralWidget);
        endFilteredChatsState->setObjectName(QStringLiteral("endFilteredChatsState"));
        endFilteredChatsState->setMinimumSize(QSize(200, 0));
        endFilteredChatsState->setMaximumSize(QSize(500, 16777215));
        endFilteredChatsState->setTristate(true);

        horizontalLayout->addWidget(endFilteredChatsState);

        unneededChatsHiderState = new QCheckBox(centralWidget);
        unneededChatsHiderState->setObjectName(QStringLiteral("unneededChatsHiderState"));
        unneededChatsHiderState->setMinimumSize(QSize(200, 0));
        unneededChatsHiderState->setTristate(true);

        horizontalLayout->addWidget(unneededChatsHiderState);


        botListContainerGrid->addLayout(horizontalLayout, 2, 0, 1, 1);

        botListContainerGrid->setColumnMinimumWidth(0, 250);
        botListContainerGrid->setColumnMinimumWidth(1, 250);

        horizontalLayout_2->addLayout(botListContainerGrid);

        chatBotTabs = new QTabWidget(centralWidget);
        chatBotTabs->setObjectName(QStringLiteral("chatBotTabs"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(255);
        sizePolicy1.setVerticalStretch(255);
        sizePolicy1.setHeightForWidth(chatBotTabs->sizePolicy().hasHeightForWidth());
        chatBotTabs->setSizePolicy(sizePolicy1);
        chatBotTabs->setMinimumSize(QSize(521, 281));

        horizontalLayout_2->addWidget(chatBotTabs);

        QT_TestClass->setCentralWidget(centralWidget);

        retranslateUi(QT_TestClass);

        chatBotTabs->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(QT_TestClass);
    } // setupUi

    void retranslateUi(QMainWindow *QT_TestClass)
    {
        QT_TestClass->setWindowTitle(QApplication::translate("QT_TestClass", "PA ChatBot", 0));
        onlineCountLabel->setText(QApplication::translate("QT_TestClass", "0 Online | 0 Started", 0));
        chatProxySubmit->setText(QApplication::translate("QT_TestClass", "Add Proxies", 0));
        reloadFiltersSubmit->setText(QApplication::translate("QT_TestClass", "Reload Filters", 0));
        chatManagerRequestNewChat->setText(QApplication::translate("QT_TestClass", "New Chat", 0));
        autoSenderState->setText(QApplication::translate("QT_TestClass", "Story Mode", 0));
        autoAIModeCheckBox->setText(QApplication::translate("QT_TestClass", "AI Mode", 0));
        autoSearchCheckBox->setText(QApplication::translate("QT_TestClass", "Automatic Search", 0));
        chatManagerFillBots->setText(QApplication::translate("QT_TestClass", "Fill Bots", 0));
        autoSendIntroductionMessage->setText(QApplication::translate("QT_TestClass", "Send Intro Message", 0));
        chatManagerAddBot->setText(QApplication::translate("QT_TestClass", "Add New Bot", 0));
        endFilteredChatsState->setText(QApplication::translate("QT_TestClass", "End Filtered Chats", 0));
        unneededChatsHiderState->setText(QApplication::translate("QT_TestClass", "Hide Unneeded Chats", 0));
    } // retranslateUi

};

namespace Ui {
    class QT_TestClass: public Ui_QT_TestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_TEST_H
