#pragma once
#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QListView>
#include <QMap>
#include "PAChatClient.h"

class PAChatClientViewItem : public QAbstractItemView
{

};

class PAChatManager : public QObject
{
	Q_OBJECT
public:
	PAChatManager(QObject *parent = Q_NULLPTR);
	~PAChatManager();
};

