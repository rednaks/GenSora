#ifndef AUTH_WINDOW_H
#define AUTH_WINDOW_H
#include <QtGui>
#include "registerWindow.h"
#include "contactWindow.h"

class AuthWindow: public QMainWindow {
	Q_OBJECT

public:
	AuthWindow();
	~AuthWindow();

private slots:
	void openRegisterWindow();
	void openContactWindow();

private:
	QLabel *pseudoLabel;
	QLabel *passwordLabel;
	QLineEdit *pseudoLineEdit;
	QLineEdit *passwordLineEdit;
	QPushButton *loginButton;
	QPushButton *registerButton;

};
#endif
