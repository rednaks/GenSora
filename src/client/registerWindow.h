#ifndef REGISTER_WINDOW_H
#define REGISTER_WINDOW_H
#include <QtGui>
#include "net.h"
#include "../common/user.h"
#include "../common/message.h"
#include <iostream>
#include <sstream>


class RegisterWindow: public QDialog {
	Q_OBJECT

public: 
	RegisterWindow(QWidget *parent = 0, QString = "",QString = "");
	~RegisterWindow();
private slots:
	void submitData();
	void verifData();
	void subscriptionResponse(const QString &);
	void quitWin();
protected:
	void closeEvent(QCloseEvent *event);
private:
	/*Les Labels */
	QLabel *nomLabel;
	QLabel *prenomLabel;
	QLabel *emailLabel;
	QLabel *pseudoLabel;
	QLabel *passwordLabel;
	QLabel *passwordVLabel;

	/*Les Inputs */
	QLineEdit *nomLineEdit;
	QLineEdit *prenomLineEdit;
	QLineEdit *emailLineEdit;
	QLineEdit *pseudoLineEdit;
	QLineEdit *passwordLineEdit;
	QLineEdit *passwordVLineEdit;

	/*Les buttons */
	QPushButton *submitButton;
	QPushButton *cancelButton;
	
	/*La connection */
	Net *connection;

	void openRegisterWindow();
	
};
#endif
