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

	void PushClient();
	void PopClient();
public:
	PAChatManager(
		QListWidget* proxy_entry_item_list_widget, 
		QLineEdit* proxy_entries_textedit, 
		QPushButton* proxy_entries_submit_button, 

		QObject *parent = Q_NULLPTR);
	~PAChatManager();
};
