#ifndef AUTH_WINDOW_H
#define AUTH_WINDOW_H
#include <QtGui>

class AuthWindow: public QMainWindow {
	Q_OBJECT

public:
	AuthWindow();
	~AuthWindow();


private:
	QLabel *pseudoLabel;
	QLabel *passwordLabel;
	QLineEdit *pseudoLineEdit;
	QLineEdit *passwordLineEdit;
	QPushButton *loginButton;
	QPushButton *registerButton;

};
#endif
