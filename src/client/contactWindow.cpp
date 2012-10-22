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
	connect(contactList, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(openNewTab(QListWidgetItem *)));

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
	connect(tabs, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
	

	mainLayout->addWidget(tabs);
	mainLayout->addLayout(buttonLayout);

	setWindowTitle("Liste de contacts");
	setLayout(mainLayout);
	resize(800, 600);
}

// Les Slots :
void ContactWindow::openNewTab(QListWidgetItem *item){
	DiscussionWidget *discWid = new DiscussionWidget;
	if(tabList.contains(discWid))
		return;
	tabList << discWid;
	tabs->insertTab(tabList.indexOf(discWid), discWid, item->text());
	
}
void ContactWindow::closeTab(int index){
	if(index == 0)
		return ;
	tabList.removeOne(tabs->widget(index));
	tabs->removeTab(index);
}	
