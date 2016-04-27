#pragma once
#include <unordered_set>

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QListWidget>
#include <QCheckBox>
#include <QTabWidget>

#include "PAChatClientGlue.h"
#include "ProxyList.h"

class PAChatManager : public QObject
{
	Q_OBJECT
private:
	ProxyList proxy_list_;
	std::unordered_set<PAChatClientGlue*> clients;
	QPointer<PAChatClientGlue> current_searching_;

	QPointer<QListWidget> list_view_;

	QPointer<QPushButton> add_new_bot_button_;
	QPointer<QPushButton> request_new_chat_button_;
	QPointer<QCheckBox> automatic_search_check_box_;

	QPointer<QTabWidget> tabs_container_;

	bool auto_search_enabled;

	void PushClient();
	void PopClient();

	void StartSearch();

	QTimer search_timer;
public:
	PAChatManager(
		QListWidget* proxy_entry_item_list_widget, 
		QLineEdit* proxy_entries_textedit, 
		QPushButton* proxy_entries_submit_button, 

		QListWidget* chats_list_widget,
		QTabWidget* tabs_container,

		QPushButton* add_new_bot_button,
		QPushButton* request_new_chat_button,
		QCheckBox* automatic_search_check_box,

		QObject *parent = Q_NULLPTR);
	~PAChatManager();

private Q_SLOTS:
	void onSearchDone();
	void onAutoSearcherStateChange(int state);
	void onItemSelected(QListWidgetItem * item);
};
