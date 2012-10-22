#include "contactWindow.h"

ContactWindow::ContactWindow(QWidget *parent): QWidget(parent)
{
	contactList = new QListWidget();
	addButton = new QPushButton("Ajouter");
	deleteButton = new QPushButton("Supprimer");
	
	contactList->addItem("SouGoy");
	contactList->addItem("rmh");
	contactList->addItem("skan BM");
	contactList->addItem("jmrl3");

	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addStretch();
	buttonLayout->addWidget(addButton);
	buttonLayout->addWidget(deleteButton);
	buttonLayout->addStretch();


	QVBoxLayout *mainLayout = new QVBoxLayout;
	tabs = new QTabWidget;
	tabs->setTabsClosable(true);
	tabs->insertTab(0, contactList, "Contacts");
	tabList << contactList;	
	mainLayout->addWidget(tabs);
	mainLayout->addLayout(buttonLayout);

	setWindowTitle("Liste de contacts");
	setLayout(mainLayout);
	resize(800, 600);
}

	
