#include "database.h"

DataBase::DataBase(QString req){
	request = req;
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
        db.setUserName("mpcpp");
        db.setPassword("projet");
        db.setDatabaseName("MiniProjetCpp");
	std::cout << "DEBUG dans le constructeur DataBase()"<< std::endl;
}


void DataBase::setQuery(const QString q){
	request = q;
}

void DataBase::exec()
{
	if(db.open())
	{
		QSqlQuery q;
		std::cout << "DEBUG: in function DataBase::exec(), db Opened !" << std::endl;
		std::cout << "DEBUG : in function DataBase::exec() request : " << request.toStdString() << std::endl;
		q.exec(request);
		db.close();
	}
	else
	{
		std::cout << "DEBUG :	Error ! " << db.lastError().text().toStdString() << std::endl;
	}
}
