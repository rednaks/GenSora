#include "discussionWidget.h"

DiscussionWidget::DiscussionWidget(){

	convArea = new QTextEdit;
	convArea->setReadOnly(true);
	msgArea = new QLineEdit;
	sendButton = new QPushButton("Envoyer");
	sendButton->setDefault(true);
	connect(sendButton, SIGNAL(clicked()), this, SLOT(printMsg()));
	
	QHBoxLayout *inputsLayout = new QHBoxLayout;
	inputsLayout->addWidget(msgArea);
	inputsLayout->addWidget(sendButton);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(convArea);
	mainLayout->addLayout(inputsLayout);

	setLayout(mainLayout);
}

void DiscussionWidget::setText(QString sender, QString content){

	QString msg(QTime::currentTime().toString()+" <strong>"+sender+"</strong> : "+content);
	convArea->textCursor().insertHtml(msg);
	convArea->textCursor().insertText("\n");
	convArea->ensureCursorVisible();
	msgArea->setText("");
	if(sender == QString("Vous"))
		logMsg(this->sender, msg);
	
	logMsg(sender, msg);
}

void DiscussionWidget::printMsg(){
	QString msg(msgArea->text());
	setText("Vous", msg);	
	emit requestToSendMsg(msg, this);
}

void DiscussionWidget::logMsg(QString &sender, QString &msg){
	QFile file("history/"+sender+".html");
	if(!file.exists()){
		if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
			QTextStream oss(&file);
			oss << "<!DOCTYPE html><html><head><meta charset='utf-8'/><title>Historique de conversation </title><style type='text/css'>body {background: #f0f0f0; line-height: 25%;}</style><body>";
			file.close();
		}
	}
	if(file.open(QIODevice::Append | QIODevice::Text)){
			QTextStream oss(&file);
			oss << "<p>"+msg+"</p>";
			file.close();
	}
}

void DiscussionWidget::setSender(QString s){
	sender = s;
}
