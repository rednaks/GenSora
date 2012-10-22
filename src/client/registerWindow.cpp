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
	connect(submitButton, SIGNAL(clicked()), this, SLOT(submitData()));
	cancelButton = new QPushButton("Annuler");

	QFormLayout *formLayout = new QFormLayout;
	formLayout->addRow(nomLabel, nomLineEdit);
	formLayout->addRow(prenomLabel, prenomLineEdit);
	formLayout->addRow(emailLabel, emailLineEdit);
	formLayout->addRow(pseudoLabel, pseudoLineEdit);
	formLayout->addRow(passwordLabel, passwordLineEdit);
	formLayout->addRow(submitButton, cancelButton);
	connection = new Net;
	
	setLayout(formLayout);
	
}


void RegisterWindow::submitData(){

	User u;


	u.setNom(nomLineEdit->text().toStdString());
        u.setPrenom(prenomLineEdit->text().toStdString());
        u.setEmail(emailLineEdit->text().toStdString());
	u.setPseudo(pseudoLineEdit->text().toStdString());
        u.setPassword(passwordLineEdit->text().toStdString());
	/* TODO : 
	QString host("localhost");
	quint16 port(8080);
	connection->connectToServer(host, port)
	connection->sendMsg("INSCR:"+ ...);
	*/
	std::cout << "Nom : " << u.getNom() << std::endl;}


RegisterWindow::~RegisterWindow() {

}
