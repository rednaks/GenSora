#ifndef AUTH_WINDOW_H
#define AUTH_WINDOW_H
#include <QtGui>
#include "registerWindow.h"

class AuthWindow: public QMainWindow {
	Q_OBJECT

public:
	AuthWindow();
	~AuthWindow();

private slots:
	void openRegisterWindow();

private:
	QLabel *pseudoLabel;
	QLabel *passwordLabel;
	QLineEdit *pseudoLineEdit;
	QLineEdit *passwordLineEdit;
	QPushButton *loginButton;
	QPushButton *registerButton;

};
#endif
