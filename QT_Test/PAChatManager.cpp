#include "PAChatManager.h"

QT_USE_NAMESPACE

PAChatManager::PAChatManager(
	QListWidget* proxy_entry_item_list_widget,
	QLineEdit* proxy_entries_textedit,
	QPushButton* proxy_entries_submit_button,
	QPushButton* add_new_client_button,
	QPushButton* remove_client_button,
	QObject *parent
)
	: QObject(parent), 
	  proxy_list_(proxy_entry_item_list_widget, proxy_entries_textedit, proxy_entries_submit_button, this),
	  add_new_client_button_(add_new_client_button),
	  remove_client_button_(remove_client_button)
{
	connect(add_new_client_button_, &QPushButton::clicked, this, &PAChatManager::PushClient);
	connect(remove_client_button_, &QPushButton::clicked, this, &PAChatManager::PopClient);
}

PAChatManager::~PAChatManager()
{

}
