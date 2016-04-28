#pragma once
#include <QObject>

class PAChatClientFilter: public QObject
{
	Q_OBJECT
public:
	PAChatClientFilter(QObject *parent = Q_NULLPTR);
	~PAChatClientFilter();

	bool IsMessageFiltered(QString message);
};
