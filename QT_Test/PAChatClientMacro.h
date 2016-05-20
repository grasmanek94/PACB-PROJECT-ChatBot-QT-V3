#pragma once
#include <QtCore/QObject>
#include <QtWidgets/QListWidget>
#include <QtCore/QPointer>
class PAChatClientMacro: public QObject
{
	Q_OBJECT
private:
	QPointer<QListWidget> macro_list_;
public:
	PAChatClientMacro(QListWidget* macro_list, QObject *parent = Q_NULLPTR);
	~PAChatClientMacro();

private Q_SLOTS:
	void onItemDoubleClicked(QListWidgetItem * item);

Q_SIGNALS:
	void onMacroRequested(QString text);
};
