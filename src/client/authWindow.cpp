#include "authWindow.h"

AuthWindow::AuthWindow(){
	logoLabel = new QLabel();
	logoLabel->setPixmap(QPixmap("./rc/logo.png"));
	
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

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(logoLabel, 0, Qt::AlignHCenter);
	mainLayout->addLayout(formLayout);

	QWidget *mainWidget = new QWidget;

	mainWidget->setLayout(mainLayout);

	setCentralWidget(mainWidget);
	connection = new Net;
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
	User u;
	u.setPseudo(pseudoLineEdit->text().toStdString());
	u.setPassword(passwordLineEdit->text().toStdString());	
	// Sérialisation : 
		std::ostringstream oss;
		boost::archive::text_oarchive oa(oss);
		oa << u;
	//

	QString msg = "AUTH:"+QString(oss.str().c_str());
	if(connection->state() == QAbstractSocket::ConnectedState)
		return;

	connect(connection, SIGNAL(receivedDataSignal(const QString &)), this, SLOT(receivedDataSlot(const QString &)));	
	QString host("localhost");
	quint16 port(8080);
	connection->connectToServer(host, port);
	connection->sendMsg(msg);

	ContactWindow *conWin = new ContactWindow();
	conWin->show();
	//this->hide(); TODO
}

void AuthWindow::receivedDataSlot(const QString &msg){

	std::cout << "Donnée reçu dans AutWindow :" << msg.toStdString() << std::endl;
	Message m(msg);
	if(m.getType() == ERRO)
		return;
	
	if(m.getType() == AUTH){
		if(m.getContent()=="1")
			QMessageBox::information(this, "Bienvenu !", "Vous avez été authentifié avec succès");
		else if(m.getContent() == "0")
			QMessageBox::warning(this, "Erreur !", "Le pseudo ou le mot de passe sont incorrecte");
	}
}
