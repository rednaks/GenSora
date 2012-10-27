#include "net.h"

Net::Net(){
	client = new QTcpSocket(this);
	connect(client, SIGNAL(readyRead()), this, SLOT(receivedData()));
	connect(client, SIGNAL(connected()), this, SLOT(connectedSlot()));
	connect(client, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
	mSize = 0;
	getNetInfo();

}

Net::Net(Net &n){
	client = n.client;
	connect(client, SIGNAL(readyRead()), this, SLOT(receivedData()));
        connect(client, SIGNAL(connected()), this, SLOT(connectedSlot()));
        connect(client, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
        mSize = 0;
	getNetInfo();
}

// Slots : 
void Net::connectedSlot(){
	std::cout << "Connectée !" << std::endl;
}

void Net::disconnectedSlot(){
	std::cout << "Déconnecté !" << std::endl;

}

void Net::receivedData(){
	std::cout << "Donnée reçus ##NET## " << std::endl;
	QTcpSocket *sock = qobject_cast<QTcpSocket *> (sender());
	if(sock == 0)
		return;
	QDataStream in(sock);
	if(mSize == 0){
		
		if(sock->bytesAvailable() < (int) sizeof(quint16))
			return;
		in >> mSize;
	}
	if(sock->bytesAvailable() < mSize)
		return;
	QString msg;
	in >> msg;
	std::cout << msg.toStdString() << "##NET##" << std::endl;
	emit receivedDataSignal(msg);
	mSize = 0;
}

// Les Méthodes : 

void Net::sendMsg(const QString msg){
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

void Net::connectToServer(){

	client->abort();
	client->connectToHost(host, port);
}

void Net::disconnectFromServer(){
	client->disconnectFromHost();
}
bool Net::waitForConnected(){
	return client->waitForConnected(latency);
}


void Net::getNetInfo(){
	std::cout << "GETTIN NET INFO ..." << std::endl;
	QFile file("net.config");
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
		host = "localhost";
		port = (quint16)8080;
		latency = 1000;
	}
	else
	{
		host = ((QString)file.readLine()).remove('\n');
		port = ((QString)file.readLine()).remove('\n').toInt();
		latency = ((QString)file.readLine()).remove('\n').toInt();
		file.close();
	}
	std::cout << "ADDR: " << host.toStdString() << ":" << port << " LAT:" << latency << std::endl;
}
