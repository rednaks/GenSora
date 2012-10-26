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
int DataBase::exec(int i)
{
	if(db.open())
	{
	QSqlQuery q;
	std::cout << "DEBUG: in function DataBase::exec(int),db Opened !" << std::endl;
                std::cout << "DEBUG : in function DataBase::exec(int) request : " << request.toStdString() << std::endl;
               if ( q.exec(request)){
			if( q.next())
				return 1;
			else
				return 0;
	// cette valeur doit renvoyer normalement 1 ou 0 puisque le pseudo il est unique 
		}		
		else {
			std::cout << " Erreur execution requete!! " << std::endl;
		}
                db.close();
	
	}
		return -1;
	
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

QString DataBase::exec(std::string s){
	if(db.open()){
		QSqlQuery q;
		std::cout << "DEBUG : in function QString DataBase::exec(), db opened" << std::endl;
		FriendList fl;
		if(q.exec(request)){
			while(q.next()){
				std::cout << "Friend : " << q.value(0).toString().toStdString() << std::endl;
				fl << q.value(0).toString();
			}
		}
		db.close();
		std::ostringstream oss;
		boost::archive::text_oarchive oa(oss);
		oa << fl;
		return QString::fromStdString(oss.str());
	}else

		return NULL;
}	
