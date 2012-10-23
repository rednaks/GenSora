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
	QAbstractSocket::SocketState state();


private slots:
	void connectedSlot();
	void disconnectedSlot();
	void receivedData();
signals:
	void receivedDataSignal();	

private:
	QTcpSocket *client;
	quint16 mSize;
};
#endif
