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
#include "../common/user.h"
#include "../common/message.h"


class ContactWindow: public QDialog
{
	Q_OBJECT
public:
	ContactWindow(QWidget *parent = 0);
	~ContactWindow();
	void init();
	void ajouterContact(QString);

private slots:
	void openNewTab(QListWidgetItem *);
	void closeTab(int );
	void openAddContactWindow();
	void receivedData(const QString &);
	void openConfirmMsgBox();
	void fwdRequestToSendMsg(const QString &, DiscussionWidget *);

signals:
	void conReceivedDataSignal(const QString &);
	void fwdAddFriendRequest(const QString &);
	void getFriendListRequest();
	void delFriendRequest(const QString &);
	void fwdRequestToSendMsgSignal(const QString &);

protected:
	void closeEvent(QCloseEvent *);
	void keyPressEvent(QKeyEvent *);

private:
	QPushButton *addButton;
	QPushButton *deleteButton;
	QTabWidget *tabs;
	QListWidget *contactList;
	QMap<int , QWidget *> widgetIndex;
	QMap<QString, QWidget *> tabList;
	void printReceivedMsg(const QString &, const QString &);
};
#endif

