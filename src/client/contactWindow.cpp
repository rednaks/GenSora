#include "contactWindow.h"
#include "authWindow.h"
ContactWindow::ContactWindow(QWidget *parent): QDialog(parent)
{
	contactList = new QListWidget();
	addButton = new QPushButton("Ajouter");
	addButton->setIcon(QIcon("resources/contactIcons/user_add.png"));
	deleteButton = new QPushButton("Supprimer");
	deleteButton->setIcon(QIcon("resources/contactIcons/user_remove.png"));
	

	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addStretch();
	buttonLayout->addWidget(addButton);
	buttonLayout->addWidget(deleteButton);
	buttonLayout->addStretch();

	QVBoxLayout *mainLayout = new QVBoxLayout;
	tabs = new QTabWidget;
	tabs->setTabsClosable(true);
	tabs->insertTab(0, contactList, "Contacts");
	tabList.insert("Contacts", contactList);	
	widgetIndex.insert(0, contactList);
	

	mainLayout->addWidget(tabs);
	mainLayout->addLayout(buttonLayout);

	setWindowTitle("Liste de contacts");
	setLayout(mainLayout);
	resize(800, 600);
	
}

void ContactWindow::init(){
	connect(parentWidget(), SIGNAL(pRDS(const QString &)), this, SLOT(receivedData(const QString &)));
	connect(addButton, SIGNAL(clicked()), this, SLOT(openAddContactWindow()));
	connect(deleteButton, SIGNAL(clicked()), this, SLOT(openConfirmMsgBox()));
	emit getFriendListRequest();
	connect(contactList, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(openNewTab(QListWidgetItem *)));
	connect(tabs, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
	

}

// Les Slots :
void ContactWindow::openNewTab(QListWidgetItem *item){
	DiscussionWidget *discWid = new DiscussionWidget;
	if(tabList.contains(item->text())){
		tabs->setCurrentWidget(tabList.value(item->text()));
		return;
	}
	tabList.insert(item->text(),discWid);
	widgetIndex.insert(widgetIndex.end().key(),discWid);
	tabs->insertTab(widgetIndex.key(discWid)+1, discWid, item->text());
	
}
void ContactWindow::closeTab(int index){
	if(index == 0)
		return ;
	tabList.remove(tabList.key(tabs->widget(index)));
	widgetIndex.remove(index);
	tabs->removeTab(index);
}	

void ContactWindow::openAddContactWindow(){

	AddContactWindow *aw = new AddContactWindow(this);
	connect(aw, SIGNAL(addFriendRequest(const QString &)), this, SIGNAL(fwdAddFriendRequest(const QString &)));
	aw->show();
}

void ContactWindow::receivedData(const QString &msg){

	std::cout << "Received data from parent : " << msg.toStdString() << std::endl;
	Message m(msg);
	if(m.getType() == GETF){
		FriendList fl;
		std::istringstream iss(m.getContent().toStdString(),std::istringstream::in);
		boost::archive::text_iarchive ia(iss);
		ia >> fl;
		for(int i = 0; i< fl.size(); i++)
			contactList->addItem(QString::fromStdString(fl[i]));
	}
	else if(m.getType() == DELF){
		if(m.getContent() != "0"){
			QMessageBox::information(this, QString::fromUtf8("Succès"), QString::fromUtf8(("<strong>"+m.getContent()+"</strong> A été effacé de votre liste d'amis").toStdString().c_str()));

            int pos = contactList->row(contactList->findItems(m.getContent(), Qt::MatchExactly)[0]);
            contactList->takeItem(pos);
		}
	}
	else if (m.getType() == ADDF)
		emit conReceivedDataSignal(msg);
}

void ContactWindow::openConfirmMsgBox(){
	QMessageBox msgBox;
	msgBox.setText("Attention !");
	QString pseudo = contactList->currentItem()->text();
	msgBox.setInformativeText(QString::fromUtf8(("Vous êtes sûr de vouloir supprimer <strong>"+pseudo+"</strong> de votre liste d'amis ?").toStdString().c_str()));
	msgBox.setStandardButtons(QMessageBox::Yes| QMessageBox::No);
	int ret = msgBox.exec();
	if(ret == QMessageBox::Yes){
		QString msg = "DELF:"+pseudo;
		emit delFriendRequest(msg);
		std::cout << "Effacé !" << std::endl;
	}
	
}

void ContactWindow::ajouterContact(QString pseudo){
	contactList->addItem(pseudo);
}
