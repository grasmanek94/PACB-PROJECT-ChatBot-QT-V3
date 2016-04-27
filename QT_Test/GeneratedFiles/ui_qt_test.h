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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
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
    QPushButton *chatProxySubmit;
    QLineEdit *chatProxyInput;
    QListWidget *chatProxyList;
    QGridLayout *botListContainerGrid;
    QPushButton *chatManagerRequestNewChat;
    QCheckBox *autoSearchCheckBox;
    QPushButton *chatManagerAddBot;
    QListWidget *chatBoxPeers;
    QListView *preparedTextsBox;
    QCheckBox *autoSendIntroductionMessage;
    QCheckBox *autoSenderState;
    QTabWidget *chatBotTabs;

    void setupUi(QMainWindow *QT_TestClass)
    {
        if (QT_TestClass->objectName().isEmpty())
            QT_TestClass->setObjectName(QStringLiteral("QT_TestClass"));
        QT_TestClass->resize(1372, 477);
        QT_TestClass->setMinimumSize(QSize(1113, 477));
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
        QFont font;
        font.setPointSize(10);
        chatProxyList->setFont(font);

        proxyListContainerGrid->addWidget(chatProxyList, 0, 0, 1, 1);


        horizontalLayout_2->addLayout(proxyListContainerGrid);

        botListContainerGrid = new QGridLayout();
        botListContainerGrid->setSpacing(6);
        botListContainerGrid->setObjectName(QStringLiteral("botListContainerGrid"));
        botListContainerGrid->setSizeConstraint(QLayout::SetMinimumSize);
        chatManagerRequestNewChat = new QPushButton(centralWidget);
        chatManagerRequestNewChat->setObjectName(QStringLiteral("chatManagerRequestNewChat"));
        chatManagerRequestNewChat->setMaximumSize(QSize(500, 16777215));

        botListContainerGrid->addWidget(chatManagerRequestNewChat, 2, 0, 1, 1);

        autoSearchCheckBox = new QCheckBox(centralWidget);
        autoSearchCheckBox->setObjectName(QStringLiteral("autoSearchCheckBox"));
        autoSearchCheckBox->setMaximumSize(QSize(500, 16777215));
        autoSearchCheckBox->setChecked(true);

        botListContainerGrid->addWidget(autoSearchCheckBox, 3, 0, 1, 1);

        chatManagerAddBot = new QPushButton(centralWidget);
        chatManagerAddBot->setObjectName(QStringLiteral("chatManagerAddBot"));
        chatManagerAddBot->setMinimumSize(QSize(289, 23));
        chatManagerAddBot->setMaximumSize(QSize(500, 16777215));

        botListContainerGrid->addWidget(chatManagerAddBot, 1, 0, 1, 1);

        chatBoxPeers = new QListWidget(centralWidget);
        chatBoxPeers->setObjectName(QStringLiteral("chatBoxPeers"));
        chatBoxPeers->setMinimumSize(QSize(400, 250));
        chatBoxPeers->setMaximumSize(QSize(500, 16777215));
        chatBoxPeers->setFont(font);

        botListContainerGrid->addWidget(chatBoxPeers, 0, 0, 1, 1);

        preparedTextsBox = new QListView(centralWidget);
        preparedTextsBox->setObjectName(QStringLiteral("preparedTextsBox"));
        preparedTextsBox->setMinimumSize(QSize(252, 0));
        preparedTextsBox->setMaximumSize(QSize(252, 16777215));
        preparedTextsBox->setFont(font);

        botListContainerGrid->addWidget(preparedTextsBox, 0, 1, 1, 1);

        autoSendIntroductionMessage = new QCheckBox(centralWidget);
        autoSendIntroductionMessage->setObjectName(QStringLiteral("autoSendIntroductionMessage"));
        autoSendIntroductionMessage->setChecked(true);

        botListContainerGrid->addWidget(autoSendIntroductionMessage, 1, 1, 1, 1);

        autoSenderState = new QCheckBox(centralWidget);
        autoSenderState->setObjectName(QStringLiteral("autoSenderState"));
        autoSenderState->setChecked(true);

        botListContainerGrid->addWidget(autoSenderState, 2, 1, 1, 1);


        horizontalLayout_2->addLayout(botListContainerGrid);

        chatBotTabs = new QTabWidget(centralWidget);
        chatBotTabs->setObjectName(QStringLiteral("chatBotTabs"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(255);
        sizePolicy.setVerticalStretch(255);
        sizePolicy.setHeightForWidth(chatBotTabs->sizePolicy().hasHeightForWidth());
        chatBotTabs->setSizePolicy(sizePolicy);
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
        chatProxySubmit->setText(QApplication::translate("QT_TestClass", "Add Proxies", 0));
        chatManagerRequestNewChat->setText(QApplication::translate("QT_TestClass", "New Chat", 0));
        autoSearchCheckBox->setText(QApplication::translate("QT_TestClass", "Automatic Search", 0));
        chatManagerAddBot->setText(QApplication::translate("QT_TestClass", "Add New Bot", 0));
        autoSendIntroductionMessage->setText(QApplication::translate("QT_TestClass", "Send Intro Message", 0));
        autoSenderState->setText(QApplication::translate("QT_TestClass", "Story Mode", 0));
    } // retranslateUi

};

namespace Ui {
    class QT_TestClass: public Ui_QT_TestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_TEST_H
