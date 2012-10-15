#include "authWindow.h"

AuthWindow::AuthWindow(){
	pseudoLabel = new QLabel("Nom");
	passwordLabel = new QLabel("Mot de passe");
	pseudoLineEdit = new QLineEdit;
	passwordLineEdit = new QLineEdit;
	passwordLineEdit->setEchoMode(QLineEdit::Password);
	
	loginButton = new QPushButton("Se connecter");
	registerButton = new QPushButton("S'enregister");
	
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


