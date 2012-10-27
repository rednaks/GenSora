#include "message.h"

Message::Message(const QString &msg){
	message = msg;
	setHeader();
	setContent();
}

int Message::getType() {

	if(header == QString("INSC"))
		type = 0;
	else if(header == QString("AUTH"))
		type = 1;
	else if(header == QString("GETF"))
		type = 2;
	else if(header == QString("ADDF"))
		type = 3;
	else if(header == QString("DELF"))
		type = 4;
	else
		type = -1;

	return type;
}

void Message::setHeader(){
	header = message.section(':', 0, 0);
}

QString Message::getHeader(){ return header;}

void Message::setContent(){

	content = message.section(':', 1);
}

QString Message::getContent(){	return content; }
