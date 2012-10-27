#ifndef DISCUSSION_WIDGET_H
#define DISCUSSION_WIDGET_H
#include <QtGui>

class DiscussionWidget: public QWidget{
	Q_OBJECT

public:
	DiscussionWidget();
	void setText(QString, QString);

private slots:
	void printMsg();

signals:
	void requestToSendMsg(const QString &, DiscussionWidget *);

private:
	QTextEdit *convArea;
	QLineEdit *msgArea;
	QPushButton *sendButton;
};
#endif
