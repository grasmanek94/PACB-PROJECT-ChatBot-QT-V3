#include "ProxyList.h"

QT_USE_NAMESPACE

ProxyList::ProxyList(QListWidget* proxy_entry_item_list_widget, QObject *parent)
	: QObject(parent), list_view_(proxy_entry_item_list_widget)
{

}

ProxyList::~ProxyList()
{

}

bool ProxyList::Add(ProxyEntry* entry)
{
	auto exists = entries_.find(entry);

	if (exists == entries_.end())
	{
		list_view_->addItem(entry);
		return true;
	}

	return false;
}

bool ProxyList::Remove(ProxyEntry* entry)
{
	auto exists = entries_.find(entry);

	if (exists != entries_.end())
	{
		list_view_->removeItemWidget(entry);
		return true;
	}

	return false;
}

ProxyEntry* ProxyList::GetLowestCountEntry()
{
	ProxyEntry* lowest;
	size_t lowest_count;

	if (entries_.size() != 0)
	{
		lowest = entries_.begin()->first;
		lowest_count = entries_.begin()->second;
	}
	else
	{
		lowest = nullptr;
		lowest_count = 999;
	}

	for (auto& i : entries_)
	{
		if (i.second < lowest_count)
		{
			lowest_count = i.second;
			lowest = i.first;
		}
	}

	return lowest;
}

bool ProxyList::IsFull(size_t max_count)
{
	for (auto& i : entries_)
	{
		if (i.second >= max_count)
		{
			return false;
		}
	}

	return true;
}
