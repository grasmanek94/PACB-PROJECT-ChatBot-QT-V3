#pragma once
#include <vector>

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QListWidget>
#include <QCheckBox>

#include "PAChatClientGlue.h"
#include "ProxyList.h"

class PAChatManager : public QObject
{
	Q_OBJECT
private:
	ProxyList proxy_list_;
	std::vector<PAChatClientGlue*> clients;
	PAChatClientGlue* current_searching_;

	void PushClient();
	void PopClient();
public:
	PAChatManager(
		QListWidget* proxy_entry_item_list_widget, 
		QLineEdit* proxy_entries_textedit, 
		QPushButton* proxy_entries_submit_button, 
		QPushButton* request_new_chat_button,
		QCheckBox* automatic_search_check_box,
		QObject *parent = Q_NULLPTR);
	~PAChatManager();

private Q_SLOTS:
	void onSearchDone();

};
