#include "contactWindow.h"

ContactWindow::ContactWindow(QWidget *parent): QWidget(parent)
{
	contactList = new QListWidget();
	addButton = new QPushButton("Ajouter");
	addButton->setIcon(QIcon("resources/contactIcons/user_add.png"));
	deleteButton = new QPushButton("Supprimer");
	deleteButton->setIcon(QIcon("resources/contactIcons/user_remove.png"));
	
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
	tabList.insert("Contacts", contactList);	
	widgetIndex.insert(0, contactList);
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
	if(tabList.contains(item->text()))
		return;
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
