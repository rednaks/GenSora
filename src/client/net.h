#ifndef NET_H
#define NET_H
#include <QtNetwork>
#include <iostream>

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
	

private:
	QTcpSocket *client;
	quint16 mSize;
};
#endif
