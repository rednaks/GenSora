#ifndef REGISTER_WINDOW_H
#define REGISTER_WINDOW_H
#include <QtGui>
#include "net.h"

class RegisterWindow: public QDialog {
	Q_OBJECT

public: 
	RegisterWindow(QWidget *parent = 0);
	~RegisterWindow();
private slots:
	 void submitData();


private:
	/*Les Labels */
	QLabel *nomLabel;
	QLabel *prenomLabel;
	QLabel *emailLabel;
	QLabel *pseudoLabel;
	QLabel *passwordLabel;

	/*Les Inputs */
	QLineEdit *nomLineEdit;
	QLineEdit *prenomLineEdit;
	QLineEdit *emailLineEdit;
	QLineEdit *pseudoLineEdit;
	QLineEdit *passwordLineEdit;

	/*Les buttons */
	QPushButton *submitButton;
	QPushButton *cancelButton;
	
	/*La connection */
	Net *connection;

	void openRegisterWindow();
	
};
#endif
