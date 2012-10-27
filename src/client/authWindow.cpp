#include "authWindow.h"

AuthWindow::AuthWindow(){
	

	logoLabel = new QLabel();
	logoLabel->setPixmap(QPixmap("./rc/logo.png"));
	
	pseudoLabel = new QLabel("Pseudo");
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

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(logoLabel, 0, Qt::AlignHCenter);
	mainLayout->addLayout(formLayout);

	QWidget *mainWidget = new QWidget;

	mainWidget->setLayout(mainLayout);

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
	 QString pseudoAuth,passwordAuth;
        pseudoAuth = pseudoLineEdit->text();
        passwordAuth = passwordLineEdit->text();

	RegisterWindow *regWin = new RegisterWindow(this, pseudoAuth, passwordAuth);
	regWin->show();
	
}

void AuthWindow::openContactWindow(){
	User u;
	u.setPseudo(pseudoLineEdit->text().toStdString());
	u.setPassword(passwordLineEdit->text().toStdString());	
	// Sérialisation : 
		std::ostringstream oss;
		boost::archive::text_oarchive oa(oss);
		oa << u;
	//

	QString msg = "AUTH:"+QString(oss.str().c_str());
	connection = new Net;
	if(connection->state() == QAbstractSocket::ConnectedState)
		return;

	connect(connection, SIGNAL(receivedDataSignal(const QString &)), this, SLOT(receivedDataSlot(const QString &)));	
	connection->connectToServer();
	std::cout << "STATE : " << connection->state() << std::endl;
	if(connection->waitForConnected(1000))
			connection->sendMsg(msg);
	else{
		QMessageBox::warning(this, "Erreur !", QString::fromUtf8("Impossible de se connecter au serveur.\nVérifier votre connexion internet"));
		delete connection;
	}

}

void AuthWindow::receivedDataSlot(const QString &msg){

	std::cout << "Donnée reçu dans AutWindow :" << msg.toStdString() << std::endl;
	Message m(msg);
	if(m.getType() == ERRO){
		std::cout << "ERRO TYPE " << std::endl;
//		connection->disconnectFromServer();
//		delete connection;
		return;
	}
	
	if(m.getType() == AUTH){
		if(m.getContent()=="1"){
			QMessageBox::information(this, "Bienvenu !", QString::fromUtf8("Vous avez été authentifié avec succès"));
			ContactWindow *conWin = new ContactWindow(this);
			connect(conWin, SIGNAL(fwdAddFriendRequest(const QString &)), this, SLOT(sendFriendRequest(const QString &)));
			connect(conWin, SIGNAL(getFriendListRequest()), this, SLOT(sendGetFriendRequest()));
			connect(conWin, SIGNAL(delFriendRequest(const QString &)), this, SLOT(sendFriendRequest(const QString &)));
			connect(conWin, SIGNAL(fwdRequestToSendMsgSignal(const QString &)), this, SLOT(sendFriendRequest(const QString &)));
			conWin->init();
        		//this->hide(); 
			conWin->show();
		}
		else if(m.getContent() == "0"){
			QMessageBox::warning(this, "Erreur !", "Le pseudo ou le mot de passe sont incorrecte");
			connection->disconnectFromServer();
			delete connection;
		}
	}

	if(m.getType() == ADDF || m.getType() == GETF || m.getType() == DELF || m.getType() == TMSG)
		emit pRDS(msg);

}

void AuthWindow::sendFriendRequest(const QString &msg){

	connection->sendMsg(msg);
}

void AuthWindow::sendGetFriendRequest(){
	std::cout << "SENDING FRIEND REQUEST " << std::endl;
	QString msg("GETF:"+pseudoLineEdit->text());
	connection->sendMsg(msg);
}

