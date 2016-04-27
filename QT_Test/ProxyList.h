#pragma once
#include <unordered_set>

#include <QtCore/QObject>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QPointer>
#include "ProxyEntry.h"

class ProxyList : public QObject
{
	Q_OBJECT
private:
	QPointer<QListWidget> list_view_;
	QPointer<QLineEdit> input_area_;
	QPointer<QPushButton> input_submit_;

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
