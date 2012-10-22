#ifndef CONTACT_WINDOW_H
#define CONTACT_WINDOW_H
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QTabWidget>
#include "discussionWidget.h"


class ContactWindow: public QWidget
{
	Q_OBJECT
public:
	ContactWindow(QWidget *parent = 0);

private slots:
	void openNewTab(QListWidgetItem *);
	void closeTab(int );

private:
	QPushButton *addButton;
	QPushButton *deleteButton;
	QTabWidget *tabs;
	QListWidget *contactList;
	QList<QWidget *> tabList;
};
#endif

