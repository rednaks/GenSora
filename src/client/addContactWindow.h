#ifndef ADD_CONTACT_WINDOW_H
#define ADD_CONTACT_WINDOW_H
#include <QtGui>
#include "contactWindow.h"
#include "net.h"
#include "message.h"

class AddContactWindow: public QDialog{
	Q_OBJECT

public:
	AddContactWindow(QWidget *parent = 0); 


private slots:
	void checkField();
	void closeAddContactWindow();
	void receivedData(const QString &);

signals:
	void addFriendRequest(const QString &);

private:
	QLabel *msgLabel;
	QLabel *pseudoLabel;
	QLineEdit *pseudoLineEdit;
	QPushButton *addButton;
	QPushButton *cancelButton;
};
#endif
