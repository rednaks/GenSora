#ifndef AUTH_WINDOW_H
#define AUTH_WINDOW_H
#include <QtGui>
#include "registerWindow.h"
#include "contactWindow.h"
#include "net.h"
#include "user.h"

class AuthWindow: public QMainWindow {
	Q_OBJECT

public:
	AuthWindow();
	~AuthWindow();

private slots:
	void openRegisterWindow();
	void openContactWindow();
	void receivedDataSlot(const QString &);
	void sendFriendRequest(const QString &);
	void sendGetFriendRequest();

signals:
	void pRDS(const QString &);

private:
	QLabel *pseudoLabel;
	QLabel *passwordLabel;
	QLineEdit *pseudoLineEdit;
	QLineEdit *passwordLineEdit;
	QPushButton *loginButton;
	QPushButton *registerButton;
	QLabel *logoLabel;
	QLabel *infoLabel;
	Net *connection;

};
#endif
