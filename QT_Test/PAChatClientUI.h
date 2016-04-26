#pragma once
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

class PAChatClientUI : public QObject
{
	Q_OBJECT
private:
	QWidget* tab_;
	QGridLayout* tab_grid_layout_;
	QGridLayout* chat_container_grid_;
	QHBoxLayout* chat_container_button_grid_;
	QPushButton* chat_manager_bot_remove_;
	QPushButton* chat_manager_keep_chat_;
	QPushButton* chat_manager_end_chat_;
	QPushButton* chat_manager_send_;
	QTextEdit* chat_box_text_messages_;
	QLineEdit* chat_box_text_input_message_;

	QTabWidget* tabs_container_;
public:
	PAChatClientUI(QTabWidget* tabs_container, QObject *parent = Q_NULLPTR);
	~PAChatClientUI(); // TODO : figure out how to properly clenaup this shit....

	void ScrollToBottom();
	void ScrollToTop();

	void AddMessage(bool me, const QString& message);
	void RemoveMessages();
};
