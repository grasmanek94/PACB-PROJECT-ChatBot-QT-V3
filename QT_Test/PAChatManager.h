#pragma once
#include <map>

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QListWidget>

#include "PAChatClient.h"
#include "ProxyList.h"

class PAChatManager : public QObject
{
	Q_OBJECT
private:
	ProxyList proxy_list_;
	std::map<PAChatClient*, ProxyEntry*> clients;
public:
	PAChatManager(QListWidget* proxy_entry_item_list_widget, QLineEdit* proxy_entries_textedit, QPushButton* proxy_entries_submit_button, QPushButton* add_new_client_button, QObject *parent = Q_NULLPTR);
	~PAChatManager();
};
