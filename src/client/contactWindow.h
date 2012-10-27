#ifndef CONTACT_WINDOW_H
#define CONTACT_WINDOW_H
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QTabWidget>
#include "discussionWidget.h"
#include "addContactWindow.h"
#include "authWindow.h"


class ContactWindow: public QDialog
{
	Q_OBJECT
public:
	ContactWindow(QWidget *parent = 0);
	void init();

private slots:
	void openNewTab(QListWidgetItem *);
	void closeTab(int );
	void openAddContactWindow();
	void receivedData(const QString &);
	void openConfirmMsgBox();

signals:
	void conReceivedDataSignal(const QString &);
	void fwdAddFriendRequest(const QString &);
	void getFriendListRequest();
	void delFriendRequest(const QString &);

private:
	QPushButton *addButton;
	QPushButton *deleteButton;
	QTabWidget *tabs;
	QListWidget *contactList;
	QMap<int , QWidget *> widgetIndex;
	QMap<QString, QWidget *> tabList;
};
#endif

