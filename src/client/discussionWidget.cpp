#include "discussionWidget.h"

DiscussionWidget::DiscussionWidget(){

	convArea = new QTextEdit;
	convArea->setReadOnly(true);
	msgArea = new QLineEdit;
	sendButton = new QPushButton("Envoyer");
	
	QHBoxLayout *inputsLayout = new QHBoxLayout;
	inputsLayout->addWidget(msgArea);
	inputsLayout->addWidget(sendButton);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(convArea);
	mainLayout->addLayout(inputsLayout);

	setLayout(mainLayout);
}

void DiscussionWidget::setText(QString s){

	convArea->textCursor().insertText(QTime::currentTime().toString()+" >> "+s+"\n");
	convArea->ensureCursorVisible();
}
