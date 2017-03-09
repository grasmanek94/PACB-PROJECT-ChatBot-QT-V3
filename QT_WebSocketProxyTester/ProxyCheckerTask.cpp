#include "ProxyCheckerTask.h"

ProxyCheckerTask::ProxyCheckerTask(QObject *parent) 
	: QObject(parent) 
{

}

void ProxyCheckerTask::run()
{
	// Do processing here

	emit finished();
}
