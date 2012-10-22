#ifndef MESSAGE_H
#define MESSAGE_H
#include <QString>

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
