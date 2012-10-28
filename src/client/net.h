#ifndef NET_H
#define NET_H
#include <QtNetwork>
#include <iostream>
#include "../common/message.h"

class Net: public QObject {
	Q_OBJECT

public:
	Net();
	Net(Net &);
	void sendMsg(const QString );
	void connectToServer();
	void disconnectFromServer();
	QAbstractSocket::SocketState state();
	bool waitForConnected();


private slots:
	void connectedSlot();
	void disconnectedSlot();
	void receivedData();
signals:
	void receivedDataSignal(const QString &);	

private:
	QTcpSocket *client;
	quint16 mSize;
	QString host;
	quint16 port;
	quint16 latency;
	void getNetInfo();
};
#endif
