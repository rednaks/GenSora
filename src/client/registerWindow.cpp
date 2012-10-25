#include "registerWindow.h"

RegisterWindow::RegisterWindow(QWidget *parent):QDialog(parent){
	
	nomLabel = new QLabel("Nom");
	prenomLabel = new QLabel(QString::fromUtf8("Prénom"));
	emailLabel = new QLabel("Email");
	pseudoLabel = new QLabel("Pseudo");
	passwordLabel = new QLabel("Mot de passe");
	passwordVLabel = new QLabel("Verification du mot de passe");
	
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
	passwordVLineEdit = new QLineEdit;
        passwordVLineEdit->setEchoMode(QLineEdit::Password);
        passwordVLineEdit->setMaxLength(255);



	submitButton = new QPushButton("Envoyer");
	connect(submitButton, SIGNAL(clicked()), this, SLOT(verifData()));
	cancelButton = new QPushButton("Annuler");

	QFormLayout *formLayout = new QFormLayout;
	formLayout->addRow(nomLabel, nomLineEdit);
	formLayout->addRow(prenomLabel, prenomLineEdit);
	formLayout->addRow(emailLabel, emailLineEdit);
	formLayout->addRow(pseudoLabel, pseudoLineEdit);
	formLayout->addRow(passwordLabel, passwordLineEdit);
	formLayout->addRow(passwordVLabel, passwordVLineEdit);
	formLayout->addRow(submitButton, cancelButton);
	//connection = new Net;
	
	setLayout(formLayout);
	
}

void RegisterWindow::verifData(){
if((passwordLineEdit->text() == passwordVLineEdit->text()) && (nomLineEdit->text().toStdString()!= "") && (prenomLineEdit->text().toStdString()!= "") && (emailLineEdit->text().toStdString() != "") && (pseudoLineEdit->text().toStdString() != "") && (passwordLineEdit->text().toStdString() != "" ))
	submitData();
else
QMessageBox::warning(this, "Erreur !", "Champs vide ou mot de passe incorherent"); 


}

void RegisterWindow::submitData(){

	User u;


	u.setNom(nomLineEdit->text().toStdString());
        u.setPrenom(prenomLineEdit->text().toStdString());
        u.setEmail(emailLineEdit->text().toStdString());
	u.setPseudo(pseudoLineEdit->text().toStdString());
        u.setPassword(passwordLineEdit->text().toStdString());
	// Sérialisation de u :
	std::ostringstream oss;
	boost::archive::text_oarchive oa(oss);
	oa << u;
	//
	connection = new Net;
	connect(connection, SIGNAL(receivedDataSignal(const QString &)), this, SLOT(subscriptionResponse(const QString &)));
	QString msg = "INSC:"+QString(oss.str().c_str());
	
	if(connection->state() == QAbstractSocket::ConnectedState)
		return;
 
	QString host("localhost");
	quint16 port(8080);
	connection->connectToServer(host, port);
	if(connection->waitForConnected(1000))
		connection->sendMsg(msg);
	else {
		QMessageBox::warning(this, "Erreur", QString::fromUtf8("Impossible de sonnecter au serveur.\nVérifiez votre connexion internet"));
		delete connection;
	}

}


void RegisterWindow::subscriptionResponse(const QString &r){
	std::cout << "Réponse de l'inscription depuis le serveur" << std::endl;
	Message m(r);
	std::cout << m.getType() << ":" << m.getContent().toStdString() << std::endl;
	if(m.getType()== ERRO){
		connection->disconnectFromServer();
		return; 
	}

	if(m.getType() == INSC){
		if(m.getContent() == "0")
			QMessageBox::information(this, "Bienvenu !",QString::fromUtf8("Vous avez été inscrit avec succès"));
		else if(m.getContent() == "1"){
			QMessageBox::warning(this, "Erreur !", QString::fromUtf8("Pseuo ou addresse email existant"));
		}
	}
	
	connection->disconnectFromServer();
	delete connection;
}

RegisterWindow::~RegisterWindow() {

}
