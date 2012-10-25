#ifndef NET_H
#define NET_H
#include <QtNetwork>
#include <iostream>
#include "message.h"

class Net: public QObject {
	Q_OBJECT

public:
	Net();
	void sendMsg(const QString );
	void connectToServer(QString &, quint16 &);
	void disconnectFromServer();
	QAbstractSocket::SocketState state();
	bool waitForConnected(int);


private slots:
	void connectedSlot();
	void disconnectedSlot();
	void receivedData();
signals:
	void receivedDataSignal(const QString &);	

private:
	QTcpSocket *client;
	quint16 mSize;
};
#endif
