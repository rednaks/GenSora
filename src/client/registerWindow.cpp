#include "registerWindow.h"

RegisterWindow::RegisterWindow(QWidget *parent):QDialog(parent){
	
	nomLabel = new QLabel("Nom");
	prenomLabel = new QLabel(QString::fromUtf8("Prénom"));
	emailLabel = new QLabel("Email");
	pseudoLabel = new QLabel("Pseudo");
	passwordLabel = new QLabel("Mot de passe");
	
	nomLineEdit = new QLineEdit;
	nomLineEdit->setMaxLength(255);
	prenomLineEdit = new QLineEdit;
	prenomLineEdit->setMaxLength(255);
	emailLineEdit = new QLineEdit;
	/* Faire en sorte que l'utilisateur entre un email valide */
	QRegExp rx("^[_a-z0-9-]+(\\.[_a-z0-9-]+)*@[a-z0-9-]+(\\.[a-z0-9-]+)*(\\.[a-z]{2,4})$");
	QValidator *validator = new QRegExpValidator(rx, this);
	emailLineEdit->setValidator(validator);
	emailLineEdit->setMaxLength(255);

	pseudoLineEdit = new QLineEdit;
	pseudoLineEdit->setMaxLength(50);	
	passwordLineEdit = new QLineEdit;
	passwordLineEdit->setEchoMode(QLineEdit::Password);
	passwordLineEdit->setMaxLength(255);


	submitButton = new QPushButton("Envoyer");
	cancelButton = new QPushButton("Annuler");

	QFormLayout *formLayout = new QFormLayout;
	formLayout->addRow(nomLabel, nomLineEdit);
	formLayout->addRow(prenomLabel, prenomLineEdit);
	formLayout->addRow(emailLabel, emailLineEdit);
	formLayout->addRow(pseudoLabel, pseudoLineEdit);
	formLayout->addRow(passwordLabel, passwordLineEdit);
	formLayout->addRow(submitButton, cancelButton);
	
	setLayout(formLayout);
	
}

RegisterWindow::~RegisterWindow() {

}
