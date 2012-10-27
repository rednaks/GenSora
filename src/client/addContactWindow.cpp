#include "addContactWindow.h"

AddContactWindow::AddContactWindow(QWidget *parent): QDialog(parent){
	pseudoLabel = new QLabel("Pseudo");
	pseudoLineEdit = new QLineEdit;
	
	addButton = new QPushButton("Ajouter");
	cancelButton = new QPushButton("Annuler");
	
	connect(addButton, SIGNAL(clicked()), this, SLOT(checkField()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(closeAddContactWindow()));

	//connection = new Net(con);
	connect(parentWidget(), SIGNAL(conReceivedDataSignal(const QString &)), this, SLOT(receivedData(const QString &)));
	
	QFormLayout *formLayout = new QFormLayout;
	formLayout->addRow(pseudoLabel, pseudoLineEdit);
	formLayout->addRow(addButton, cancelButton);
	
	QVBoxLayout *mainLayout = new QVBoxLayout;
	msgLabel = new QLabel(QString::fromUtf8("Entrez le pseudo de l'ami à chercher"));
	mainLayout->addWidget(msgLabel);
	mainLayout->addLayout(formLayout);
	setLayout(mainLayout);
}

// Les slots : 
void AddContactWindow::checkField(){
	if(pseudoLineEdit->text().toStdString() == "")
		return;
	emit addFriendRequest("ADDF:"+pseudoLineEdit->text());
	pseudoLineEdit->setEnabled(false);
}

void AddContactWindow::closeAddContactWindow(){

	this->close();
}

void AddContactWindow::receivedData(const QString &msg){
	Message m(msg);
	std::cout << m.getType() << ":" << m.getContent().toStdString() << std::endl;
	if(m.getType() == ERRO){
		QMessageBox::warning(this, "Erreur !", "Une erreur s'est produite.");
		return;
	}

	if(m.getType() == ADDF){
		if(m.getContent() == "0"){
			QMessageBox::information(this, QString::fromUtf8("Succès"), pseudoLineEdit->text()+QString::fromUtf8(" a été ajouté à votre liste d'amis"));
			((ContactWindow*)parentWidget())->ajouterContact(pseudoLineEdit->text());
		}
		else 
			QMessageBox::warning(this, "Erreur", pseudoLineEdit->text()+QString::fromUtf8(" n'a pas pu être ajouté à votre liste d'amis"));
	}
}
		
