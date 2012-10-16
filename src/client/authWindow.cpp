#include "authWindow.h"

AuthWindow::AuthWindow(){
	pseudoLabel = new QLabel("Nom");
	passwordLabel = new QLabel("Mot de passe");
	pseudoLineEdit = new QLineEdit;
	passwordLineEdit = new QLineEdit;
	passwordLineEdit->setEchoMode(QLineEdit::Password);
	
	loginButton = new QPushButton("Se connecter");
	connect(loginButton, SIGNAL(clicked()), this, SLOT(openContactWindow()));
	registerButton = new QPushButton("S'enregister");
	connect(registerButton, SIGNAL(clicked()), this, SLOT(openRegisterWindow()));
	
	QFormLayout *formLayout = new QFormLayout;
	formLayout->addRow(pseudoLabel, pseudoLineEdit);
	formLayout->addRow(passwordLabel, passwordLineEdit);
	formLayout->addRow(loginButton, registerButton);
	QWidget *mainWidget = new QWidget;
	mainWidget->setLayout(formLayout);

	setCentralWidget(mainWidget);
}

AuthWindow::~AuthWindow(){

	delete pseudoLabel;
	delete passwordLabel;
	delete pseudoLineEdit;
	delete passwordLineEdit;
	delete loginButton;
	delete registerButton;
}
void AuthWindow::openRegisterWindow(){
	RegisterWindow *regWin = new RegisterWindow(this);
	regWin->show();
}

void AuthWindow::openContactWindow(){
	ContactWindow *conWin = new ContactWindow();
	conWin->show();
	//this->hide(); TODO
}
