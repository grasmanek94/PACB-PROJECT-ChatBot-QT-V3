#pragma once
#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QListWidget>
#include "PAChatClient.h"
#include "ProxyList.h"

class PAChatManager : public QObject
{
	Q_OBJECT
public:
	PAChatManager(QObject *parent = Q_NULLPTR);
	~PAChatManager();
};
