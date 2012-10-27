#include "message.h"

Message::Message(const QString &msg){
	message = msg;
	setHeader();
	setContent();
}

int Message::getType() {

	if(header == QString("INSC"))
		type = INSC;
	else if(header == QString("AUTH"))
		type = AUTH;
	else if(header == QString("GETF"))
		type = GETF;
	else if(header == QString("ADDF"))
		type = ADDF;
	else if(header == QString("DELF"))
		type = DELF;
	else if(header == QString("TMSG"))
		type = TMSG;
	else
		type = ERRO;

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
