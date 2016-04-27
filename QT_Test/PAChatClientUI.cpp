#include "PAChatClientUI.h"

PAChatClientUI::PAChatClientUI(QTabWidget* tabs_container, QObject *parent)
	: QObject(parent), tabs_container_(tabs_container)
{
	QString suffix = QString::number((size_t)this, 16);

	tab_ = new QWidget();
	tab_->setObjectName("tab_" + suffix);

	tab_grid_layout_ = new QGridLayout(tab_);
	tab_grid_layout_->setSpacing(6);
	tab_grid_layout_->setContentsMargins(11, 11, 11, 11);
	tab_grid_layout_->setObjectName("tab_grid_layout_" + suffix);

	chat_container_grid_ = new QGridLayout();
	chat_container_grid_->setSpacing(6);
	chat_container_grid_->setObjectName("chat_container_grid_" + suffix);

	chat_container_button_grid_ = new QHBoxLayout();
	chat_container_button_grid_->setSpacing(6);
	chat_container_button_grid_->setObjectName("chat_container_button_grid_" + suffix);

	chat_manager_bot_remove_ = new QPushButton(tab_);
	chat_manager_bot_remove_->setObjectName("chat_manager_bot_remove_" + suffix);
	chat_manager_bot_remove_->setMinimumSize(QSize(119, 23));

	chat_container_button_grid_->addWidget(chat_manager_bot_remove_);

	chat_manager_keep_chat_ = new QPushButton(tab_);
	chat_manager_keep_chat_->setObjectName("chat_manager_keep_chat_" + suffix);
	chat_manager_keep_chat_->setMinimumSize(QSize(119, 23));

	chat_container_button_grid_->addWidget(chat_manager_keep_chat_);

	chat_manager_end_chat_ = new QPushButton(tab_);
	chat_manager_end_chat_->setObjectName("chat_manager_end_chat_" + suffix);
	chat_manager_end_chat_->setMinimumSize(QSize(118, 23));

	chat_container_button_grid_->addWidget(chat_manager_end_chat_);

	chat_manager_send_ = new QPushButton(tab_);
	chat_manager_send_->setObjectName("chat_manager_send_" + suffix);
	chat_manager_send_->setMinimumSize(QSize(119, 23));

	chat_container_button_grid_->addWidget(chat_manager_send_);

	chat_container_grid_->addLayout(chat_container_button_grid_, 3, 0, 1, 1);

	chat_box_text_messages_ =
		new QPlainTextEdit(tab_);
		//new QTextEdit(tab_);
	chat_box_text_messages_->setObjectName("chat_box_text_messages_" + suffix);
	chat_box_text_messages_->setMinimumSize(QSize(495, 178));

	chat_container_grid_->addWidget(chat_box_text_messages_, 1, 0, 1, 1);

	chat_box_text_input_message_ = new QLineEdit(tab_);
	chat_box_text_input_message_->setObjectName("chat_box_text_input_message_" + suffix);
	chat_box_text_input_message_->setMinimumSize(QSize(495, 20));
	chat_box_text_input_message_->setMaximumSize(QSize(16777215, 16777215));

	chat_container_grid_->addWidget(chat_box_text_input_message_, 2, 0, 1, 1);

	tab_grid_layout_->addLayout(chat_container_grid_, 0, 0, 1, 1);

	chat_manager_bot_remove_->setText("Remove Bot");
	chat_manager_keep_chat_->setText("Keep Chat");
	chat_manager_end_chat_->setText("End Chat");
	chat_manager_send_->setText("Send");

	QPalette p = chat_box_text_messages_->palette();

	p.setColor(QPalette::Active, QPalette::Base, Qt::black);
	p.setColor(QPalette::Inactive, QPalette::Base, Qt::black);
	chat_box_text_messages_->setPalette(p);

	chat_box_text_messages_->setWordWrapMode(QTextOption::WordWrap);
	chat_box_text_messages_->setReadOnly(true);

	tab_number_ = tabs_container_->addTab(tab_, "");

	connect(chat_box_text_input_message_, &QLineEdit::returnPressed, this, &PAChatClientUI::onChatManagerSendChatButtonClicked);
	connect(chat_manager_send_, &QPushButton::clicked, this, &PAChatClientUI::onChatManagerSendChatButtonClicked);
	connect(chat_manager_end_chat_, &QPushButton::clicked, this, &PAChatClientUI::onChatManagerEndChatButtonClicked);
	connect(chat_manager_bot_remove_, &QPushButton::clicked, this, &PAChatClientUI::onChatManagerBotRemoveButtonClicked);
	connect(chat_manager_keep_chat_, &QPushButton::clicked, this, &PAChatClientUI::onChatManagerKeepChatButtonClicked);
	connect(chat_box_text_input_message_, &QLineEdit::textEdited, this, &PAChatClientUI::onChatManagerTextEdited);
}

void PAChatClientUI::AddMessage(bool me, const QString& message)
{
	QString style = me ?
		"background-color:rgb(255,255,255);font-size:14px;color:rgb(10,10,10);" :
		"background-color:rgb(249,86,79);font-size:14px;color:rgb(255,255,255);";

	QString format("<div style='%1'> %2 </div> <div style='font-size:3px;'> &zwnj; </div>");
	QString htmlText = format.arg(style).arg(message.toHtmlEscaped());

	chat_box_text_messages_->appendHtml(htmlText);
}

void PAChatClientUI::RemoveMessages()
{
	chat_box_text_messages_->clear();
}

void PAChatClientUI::ClearMessageInput()
{
	chat_box_text_input_message_->clear();
}

void PAChatClientUI::ScrollToBottom()
{
	QTextCursor c = chat_box_text_messages_->textCursor();
	c.movePosition(QTextCursor::End);
	chat_box_text_messages_->setTextCursor(c);
}

void PAChatClientUI::ScrollToTop()
{
	QTextCursor c = chat_box_text_messages_->textCursor();
	c.movePosition(QTextCursor::Start);
	chat_box_text_messages_->setTextCursor(c);
}

PAChatClientUI::~PAChatClientUI()
{
	if (tabs_container_)
	{
		tabs_container_->removeTab(tab_number_);
	}
	//delete tab_;//?
	//tab_ = nullptr;//?
}

void PAChatClientUI::onChatManagerBotRemoveButtonClicked()
{
	emit onRequestRemoveBot();
}

void PAChatClientUI::onChatManagerKeepChatButtonClicked()
{
	emit onRequestChatKeep();
}

void PAChatClientUI::onChatManagerEndChatButtonClicked()
{
	emit onRequestChatEnd();
}

void PAChatClientUI::onChatManagerSendChatButtonClicked()
{
	emit onRequestChatSendMessage(chat_box_text_input_message_->text());
}

void PAChatClientUI::onChatManagerTextEdited(QString text)
{
	emit onTextInputChanged(text);
}