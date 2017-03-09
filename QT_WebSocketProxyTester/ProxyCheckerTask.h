#pragma once
#include <QObject>

class ProxyCheckerTask : public QObject
{
	Q_OBJECT
public:
	ProxyCheckerTask(QObject *parent = 0);

	public slots :
	void run();

signals:
	void finished();
};
