#pragma once
#include <map>

#include <QtCore/QObject>
#include <QListWidget>

#include "ProxyEntry.h"

class ProxyList : public QObject
{
	Q_OBJECT
private:
	QListWidget* list_view_;
	std::map<ProxyEntry*, size_t> entries_;
public:
	ProxyList(QListWidget* proxy_entry_item_list_widget, QObject *parent = Q_NULLPTR);
	~ProxyList();

	bool Add(ProxyEntry* entry);
	bool Remove(ProxyEntry* entry);

	ProxyEntry* GetLowestCountEntry();
	bool IsFull(size_t max_count = 2);
};
