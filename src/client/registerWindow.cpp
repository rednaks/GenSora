#include "registerWindow.h"

RegisterWindow::RegisterWindow(QWidget *parent):QDialog(parent){
	
	nomLabel = new QLabel("Nom");
	prenomLabel = new QLabel("Prénom");
	emailLabel = new QLabel("Email");
	pseudoLabel = new QLabel("Pseudo");
	passwordLabel = new QLabel("Mot de passe");
	
	nomLineEdit = new QLineEdit;
	prenomLineEdit = new QLineEdit;
	emailLineEdit = new QLineEdit;
	// TODO INPUT CONTROL
	pseudoLineEdit = new QLineEdit;
	passwordLineEdit = new QLineEdit;


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
