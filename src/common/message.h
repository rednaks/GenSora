#ifndef MESSAGE_H
#define MESSAGE_H

#define INSC 0
#define AUTH 1
#define GETF 2
#define ADDF 3
#define DELF 4
#define TMSG 5
#define ERRO -1

#include <QString>
#include <sstream>
#include <string>

class Message {

public:
	Message(const QString &);
	int getType();
	void setHeader();
	QString getHeader();
	void setContent();
	QString getContent();

private:
	int type;
	QString message;
	QString header;
	QString content;
};
#endif
