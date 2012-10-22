#include "server.h"

Server::Server(){

	server = new QTcpServer(this);
	// Ecoute de l'addresse 127.0.0.1:8080, si elle est libre.
	if(!server->listen(QHostAddress::LocalHost, 8080)) {
		std::cout << "Erreur : " << server->errorString().toStdString() << std::endl;
	}
	else {
		std::cout << "Connecté à " << server->serverAddress().toString().toStdString() << ":" << server->serverPort() << std::endl; 
		connect(server, SIGNAL(newConnection()), this, SLOT(newConnectionSlot()));
	}
	
	mSize = 0;
}


// Les SLOTS : 
void Server::newConnectionSlot() {
	QTcpSocket *client = server->nextPendingConnection();
	clients << client;
	
	connect(client, SIGNAL(readyRead()), this, SLOT(receivedData()));
	connect(client, SIGNAL(disconnected()), this, SLOT(disconnectedClient()));
}

void Server::receivedData(){
	QTcpSocket *sock = qobject_cast<QTcpSocket *> (sender());
	if(sock == 0) // Message vide
		return; 
	
	QDataStream in(sock); // récupérer
	if(mSize == 0){ 
		if(sock->bytesAvailable() < (int)sizeof(quint16)) // On vérifie si les donnée contienne au moin la taille du méssage.
			return;
		in >> mSize;
	}
	
	if(sock->bytesAvailable() < mSize) // On vérifie s'il y a pas eu de perte de donnée
		return;

	QString msg;
	in >> msg; // Enfin si tout s'est bien passé, on récupère le message
	// TODO : Traitement du message ...
	mSize = 0;
}


void Server::disconnectedClient(){
	QTcpSocket *sock = qobject_cast<QTcpSocket *> (sender());
	if(sock == 0)
		return;
	if(clients.contains(sock))
		clients.removeOne(sock);
	sock->deleteLater();
}
