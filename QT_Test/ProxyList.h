#pragma once
#include <unordered_set>

#include <QtCore/QObject>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include "ProxyEntry.h"

class ProxyList : public QObject
{
	Q_OBJECT
private:
	QListWidget* list_view_;
	QLineEdit* input_area_;
	QPushButton* input_submit_;

	std::unordered_set<ProxyEntry*> entries_;

	void InputSubmit(bool checked = false);
public:

	ProxyList(QListWidget* proxy_entry_item_list_widget, QLineEdit* proxy_entries_textedit, QPushButton* proxy_entries_submit_button, QObject *parent = Q_NULLPTR);
	~ProxyList();

	bool Add(ProxyEntry* entry);
	bool Remove(ProxyEntry* entry);

	ProxyEntry* GetLowestCountEntry();
	bool IsFull(size_t max_count = 2);
};
