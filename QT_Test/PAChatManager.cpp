#include "PAChatManager.h"

QT_USE_NAMESPACE

PAChatManager::PAChatManager(
	QListWidget* proxy_entry_item_list_widget,
	QLineEdit* proxy_entries_textedit,
	QPushButton* proxy_entries_submit_button,

	QListWidget* chats_list_widget,
	QTabWidget* tabs_container,

	QPushButton* add_new_bot_button,
	QPushButton* request_new_chat_button,
	QCheckBox* automatic_search_check_box,

	QCheckBox* send_intro_message_check_box,
	QCheckBox* story_mode_check_box,

	QListWidget* macro_list,

	QPushButton* fill_with_bots_button,

	QObject *parent
)
	: QObject(parent),
	  proxy_list_(proxy_entry_item_list_widget, proxy_entries_textedit, proxy_entries_submit_button, this),
	  add_new_bot_button_(add_new_bot_button),
	  request_new_chat_button_(request_new_chat_button),
	  automatic_search_check_box_(automatic_search_check_box),
	  list_view_(chats_list_widget),
	  tabs_container_(tabs_container),
	  auto_search_enabled(true),
	  current_searching_(nullptr),
	  send_intro_message_check_box_(send_intro_message_check_box),
	  story_mode_check_box_(story_mode_check_box),
	  current_active_(nullptr),
	  macro_list_(macro_list),
	  fill_with_bots_button_(fill_with_bots_button)
{
	connect(add_new_bot_button_, &QPushButton::clicked, this, &PAChatManager::PushClient); // god createh ,me,
	connect(automatic_search_check_box_, &QCheckBox::stateChanged, this, &PAChatManager::onAutoSearcherStateChange);
	connect(&search_timer, &QTimer::timeout, this, &PAChatManager::searchTimeout);
	connect(list_view_, &QListWidget::itemClicked, this, &PAChatManager::onItemSelected);
	connect(list_view_, &QListWidget::itemPressed, this, &PAChatManager::onItemSelected);
	connect(list_view_, &QListWidget::itemActivated, this, &PAChatManager::onItemSelected);

	connect(fill_with_bots_button_, &QPushButton::clicked, this, &PAChatManager::PushClientsFull);
	
	//{ ProxyEntry* entry = new ProxyEntry("", 0, &proxy_list_); proxy_list_.Add(entry); }
	{ ProxyEntry* entry = new ProxyEntry("13.94.233.218", 1080, &proxy_list_); proxy_list_.Add(entry); }
	{ ProxyEntry* entry = new ProxyEntry("13.94.238.11", 1080, &proxy_list_); proxy_list_.Add(entry); }
	{ ProxyEntry* entry = new ProxyEntry("13.94.237.20", 1080, &proxy_list_); proxy_list_.Add(entry); }
	{ ProxyEntry* entry = new ProxyEntry("13.94.235.91", 1080, &proxy_list_); proxy_list_.Add(entry); }
	{ ProxyEntry* entry = new ProxyEntry("13.94.238.168", 1080, &proxy_list_); proxy_list_.Add(entry); }
	{ ProxyEntry* entry = new ProxyEntry("13.94.238.189", 1080, &proxy_list_); proxy_list_.Add(entry); }
	{ ProxyEntry* entry = new ProxyEntry("40.68.174.46", 1080, &proxy_list_); proxy_list_.Add(entry); }
	{ ProxyEntry* entry = new ProxyEntry("13.94.234.91", 1080, &proxy_list_); proxy_list_.Add(entry); }
	{ ProxyEntry* entry = new ProxyEntry("13.94.235.232", 1080, &proxy_list_); proxy_list_.Add(entry); }
	{ ProxyEntry* entry = new ProxyEntry("13.94.233.65", 1080, &proxy_list_); proxy_list_.Add(entry); }
	{ ProxyEntry* entry = new ProxyEntry("164.132.198.193", 1080, &proxy_list_); proxy_list_.Add(entry); }
	
	chat_macros_ = new PAChatClientMacro(macro_list_, this);
	connect(chat_macros_, &PAChatClientMacro::onMacroRequested, this, &PAChatManager::onMacroRequested);
}

PAChatManager::~PAChatManager()
{

}

void PAChatManager::onItemSelected(QListWidgetItem* item)
{
	PAChatClientGlue* glue = dynamic_cast<PAChatClientGlue*>(item);
	if (glue)
	{
		QWidget* tab = glue->GetTab();
		if (tab && tabs_container_)
		{
			tabs_container_->setCurrentWidget(tab);
			tab->show();
			glue->FocusInputText();
			current_active_ = glue;
		} 
	}
}

void PAChatManager::PushClient()
{
	ProxyEntry* entry = proxy_list_.GetLowestCountEntry();
	if (proxy_list_.IsFull() || !entry)
	{
		return;
	}

	PAChatClientGlue* glue = new PAChatClientGlue(entry, tabs_container_, send_intro_message_check_box_, story_mode_check_box_, this);
	clients.insert(glue);
	list_view_->addItem(glue);

	connect(glue, &PAChatClientGlue::onRequestRemove, this, &PAChatManager::PopClient);	//plz kill     `me`

	connect(glue, &PAChatClientGlue::onGlueChatConnected, this, &PAChatManager::onChatConnected);
	connect(glue, &PAChatClientGlue::onGlueChatSearch, this, &PAChatManager::onChatSearch);
	connect(glue, &PAChatClientGlue::onGlueChatBegin, this, &PAChatManager::onChatBegin);
	connect(glue, &PAChatClientGlue::onGlueChatEnd, this, &PAChatManager::onChatEnd);
	connect(glue, &PAChatClientGlue::onGlueSocketConnected, this, &PAChatManager::onSocketConnected);
	connect(glue, &PAChatClientGlue::onGlueSocketDisconnected, this, &PAChatManager::onSocketDisconnected);

	if (!current_active_)
	{
		current_active_ = glue;
	}
}

void PAChatManager::PushClientsFull()
{
	while (!proxy_list_.IsFull())
	{
		PushClient();
	}
}

void PAChatManager::PopClient()
{
	PAChatClientGlue* glue = dynamic_cast<PAChatClientGlue*>(QObject::sender());
	PopClient2(glue);
}

void PAChatManager::PopClient2(PAChatClientGlue* glue)
{
	/*bool eq = current_active_ == glue;

	ready_to_search.erase(glue);
	clients.erase(glue);
	list_view_->removeItemWidget(glue);
	tabs_container_->removeTab(tabs_container_->indexOf(glue->GetTab()));
	delete glue;

	if (eq)
	{
		onItemSelected(*clients.begin());
	}*/
	//glue->Reconnect();
}

void PAChatManager::onSocketConnected()
{
	onChatBegin();
}

void PAChatManager::onSocketDisconnected()
{
	onChatBegin();
	PopClient();
}

void PAChatManager::onAutoSearcherStateChange(int state)
{
	auto_search_enabled = state > 0;
	if (auto_search_enabled && ready_to_search.size())
	{
		PrepareSearch(*ready_to_search.begin());
	}
}

void PAChatManager::searchTimeout()
{
	if (current_searching_)
	{
		PopClient2(current_searching_);
		if (ready_to_search.size())
		{
			PrepareSearch(*ready_to_search.begin());
		}
	}
}

void PAChatManager::PrepareSearch(PAChatClientGlue* glue)
{
	ready_to_search.insert(glue);
	if (!current_searching_ && auto_search_enabled)
	{
		current_searching_ = *ready_to_search.begin();
		ready_to_search.erase(current_searching_);
		if (current_searching_)
		{
			current_searching_->Search();
			search_timer.start(2000);
		}
	}
}

void PAChatManager::onChatBegin()
{
	PAChatClientGlue* glue = dynamic_cast<PAChatClientGlue*>(QObject::sender());
	ready_to_search.erase(glue);
	if (current_searching_ == glue)
	{
		current_searching_ = nullptr;
		search_timer.stop();
		if (ready_to_search.size())
		{
			PrepareSearch(*ready_to_search.begin());
		}
	}
}

void PAChatManager::onChatConnected()
{
	PAChatClientGlue* glue = dynamic_cast<PAChatClientGlue*>(QObject::sender());
	PrepareSearch(glue);
}

void PAChatManager::onChatSearch()
{
	PAChatClientGlue* glue = dynamic_cast<PAChatClientGlue*>(QObject::sender());
	ready_to_search.erase(glue);
}


void PAChatManager::onChatEnd()
{
	PAChatClientGlue* glue = dynamic_cast<PAChatClientGlue*>(QObject::sender());
	PrepareSearch(glue);
}

void PAChatManager::onMacroRequested(QString text)
{
	if (current_active_)
	{
		current_active_->SendMessage(text);
	}
}
