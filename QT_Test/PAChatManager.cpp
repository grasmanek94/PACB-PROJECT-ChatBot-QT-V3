#include "PAChatManager.h"

QT_USE_NAMESPACE

PAChatManager::PAChatManager(QListWidget* proxy_entry_item_list_widget, QLineEdit* proxy_entries_textedit, QPushButton* proxy_entries_submit_button, QObject *parent)
	: QObject(parent), proxy_list_(proxy_entry_item_list_widget, proxy_entries_textedit, proxy_entries_submit_button, this)
{

}

PAChatManager::~PAChatManager()
{

}
