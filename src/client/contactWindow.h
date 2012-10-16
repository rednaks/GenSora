#ifndef CONTACT_WINDOW_H
#define CONTACT_WINDOW_H
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>


class ContactWindow: public QWidget
{
	Q_OBJECT
public:
	ContactWindow(QWidget *parent = 0);
private:
	QPushButton *addButton;
	QPushButton *deleteButton;
	QListWidget *contactList;
};
#endif

