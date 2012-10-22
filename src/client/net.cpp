#include "net.h"

Net::Net(){
	client = new QTcpSocket(this);
	connect(client, SIGNAL(readyRead()), this, SLOT(receivedData()));
	connect(client, SIGNAL(connected()), this, SLOT(connectedSlot()));
	connect(client, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
	mSize = 0;

}

// Slots : 
void Net::connectedSlot(){
	std::cout << "Connectée !" << std::endl;
}

void Net::disconnectedSlot(){
	std::cout << "Déconnecté !" << std::endl;

}

void Net::receivedData(){
	std::cout << "Donnée reçus " << std::endl;
}

// Les Méthodes : 

void Net::sendMsg(QString &msg){
	QByteArray packet;
	QDataStream out(&packet, QIODevice::WriteOnly);
	out << (quint16) 0;
	out << msg;
	out.device()->seek(0);
	out << (quint16) (packet.size() - sizeof(quint16));	
	client->write(packet);
}

QAbstractSocket::SocketState Net::state(){
	return client->state();
}

void Net::connectToServer(QString &host, quint16 &port){

	client->abort();
	client->connectToHost(host, port);
}
