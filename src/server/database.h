#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>
#include <QString>
#include <iostream>

class DataBase
{
public:
	DataBase(QString = " ");	
	void setQuery(const QString);
	void exec();

private:
	QSqlDatabase db;
	QString request;


};
#endif
