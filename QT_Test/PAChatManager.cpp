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
	  macro_list_(macro_list)
{
	connect(add_new_bot_button, &QPushButton::clicked, this, &PAChatManager::PushClient); // god createh ,me,
	connect(automatic_search_check_box_, &QCheckBox::stateChanged, this, &PAChatManager::onAutoSearcherStateChange);
	connect(&search_timer, &QTimer::timeout, this, &PAChatManager::StartSearch);
	connect(list_view_, &QListWidget::itemClicked, this, &PAChatManager::onItemSelected);
	connect(list_view_, &QListWidget::itemPressed, this, &PAChatManager::onItemSelected);
	connect(list_view_, &QListWidget::itemActivated, this, &PAChatManager::onItemSelected);

	ProxyEntry* entry = new ProxyEntry("", 0, &proxy_list_);
	proxy_list_.Add(entry);

	chat_macros_ = new PAChatClientMacro(macro_list_, this);
	connect(chat_macros_, &PAChatClientMacro::onMacroRequested, this, &PAChatManager::onMacroRequested);

	search_timer.start(250);
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
		tabs_container_->setCurrentWidget(tab);
		tab->show();
		glue->FocusInputText();
		current_active_ = glue;
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
	connect(glue, &PAChatClientGlue::onSearchDone, this, &PAChatManager::onSearchDone);

	if (!current_active_)
	{
		current_active_ = glue;
	}

	StartSearch();
}

void PAChatManager::PopClient()
{
	PAChatClientGlue* glue = dynamic_cast<PAChatClientGlue*>(QObject::sender());
	bool eq = current_active_ == glue;

	clients.erase(glue);
	list_view_->removeItemWidget(glue);
	tabs_container_->removeTab(tabs_container_->indexOf(glue->GetTab()));
	delete glue;

	if (eq)
	{
		onItemSelected(*clients.begin());
	}
}

void PAChatManager::onAutoSearcherStateChange(int state)
{
	auto_search_enabled = state > 0;
	StartSearch();
}

void PAChatManager::onSearchDone()
{
	current_searching_ = nullptr;
	StartSearch();
}

void PAChatManager::StartSearch()
{
	if (auto_search_enabled && !current_searching_)
	{
		for (auto& client : clients)
		{
			if (client->ReadyForSearch())
			{
				client->Search();
				current_searching_ = client;
			}
		}
	}
}

void PAChatManager::onMacroRequested(QString text)
{
	if (current_active_)
	{
		current_active_->SendMessage(text);
	}
}
