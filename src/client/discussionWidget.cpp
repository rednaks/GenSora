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

	convArea->textCursor().insertHtml(QTime::currentTime().toString()+" <strong>"+sender+"</strong> >> "+content);
	convArea->textCursor().insertText("\n");
	convArea->ensureCursorVisible();
	msgArea->setText("");
}

void DiscussionWidget::printMsg(){
	QString msg(msgArea->text());
	setText("Vous", msg);	
	emit requestToSendMsg(msg, this);
}
