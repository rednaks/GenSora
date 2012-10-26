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
	std::cout << "Nouvelle connection" << std::endl;
	
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
	traitMsg(msg, sock);
	mSize = 0;
}


void Server::disconnectedClient(){
	std::cout << "DEBug : dans le slot : disconnectedClient()" << std::endl;
	QTcpSocket *sock = qobject_cast<QTcpSocket *> (sender());
	/*if(sock == 0)
		return;*/
	if(clients.contains(sock)){
		std::cout << "Un client s'est déconnecté" << std::endl;
		clients.removeOne(sock);
		authClients.remove(authClients.key(sock));
	}
	sock->deleteLater();
}

// Les méthodes :

void Server::sendMsg(const QString &msg, QTcpSocket *client){
	QByteArray packet;
	QDataStream out(&packet, QIODevice::WriteOnly);
	out << (quint16) 0;
	out << msg;
	out.device()->seek(0);
	out << (quint16) (packet.size() - sizeof(quint16));
	client->write(packet);
}

void Server::traitMsg(const QString &msg, QTcpSocket *sock){

	//TODO : traitement du message.
	Message m(msg);
	
	std::cout << "DEBUG : Msg à traiter : " << msg.toStdString() << std::endl;
	if(m.getType() == ERRO)
		return;
	
	DataBase db;
	std::istringstream *iss;
	if(m.getType() == INSC){
		User u;
		std::string q;
		iss = new std::istringstream(m.getContent().toStdString(), std::istringstream::in);
		boost::archive::text_iarchive ia(*iss);
		ia >> u;
		// Vérification si les donnée existe dans la base :
		q = "SELECT * FROM Users where pseudo = '"+u.getPseudo()+"' AND email='"+u.getEmail()+"';";
		db.setQuery(QString(q.c_str()));
		int resp = db.exec(1);
		if(resp == 0){ // Tout va bien, l'utilisateur n'existe pas, on l'inscrit dans la base.
			q = "INSERT INTO Users(Id, pseudo, nom, prenom, email, mdp, etat) VALUES('', '"+u.getPseudo()+"', '"+u.getNom()+"', '"+u.getPrenom()+"', '"+u.getEmail()+"', '"+u.getPassword()+"', '1');";
			db.setQuery(QString(q.c_str()));
			db.exec();
		}
		std::cout << "Envoi de la réponse d'inscription" << std::endl;
		std::ostringstream oss;
		oss << resp;
		QString msg(QString::fromStdString("INSC:"+oss.str()));
		sendMsg(msg,clients[0]);
	}
	else if(m.getType() == AUTH){
		User u;
		iss = new std::istringstream(m.getContent().toStdString(), std::istringstream::in);
		boost::archive::text_iarchive ia(*iss);
		ia >> u;
                std::string q("SELECT pseudo,mdp from Users WHERE pseudo='"+u.getPseudo()+"' AND mdp='"+u.getPassword()+"';");
		db.setQuery(QString(q.c_str()));
		int rep=db.exec(1);
		std::ostringstream oss;
		oss << rep;
		QString msg(QString::fromStdString("AUTH:"+oss.str()));
		sendMsg(msg, sock);
		if(rep == 1)
			authClients.insert(QString::fromStdString(u.getPseudo()), sock);
	}
	else if(m.getType() == ADDF){
		std::string pseudo(m.getContent().toStdString());
		// Chercher si le contact existe dans la base ou non
		std::string q("SELECT * FROM Users where pseudo ='"+pseudo+"';");
		db.setQuery(QString(q.c_str()));
		int rep = db.exec(1);
		if(rep == 0){ // si l'utilisateur n'existe pas on revoi une erreur.
			QString msg("ADDF:1");
			sendMsg(msg, sock);
			return;
		}
		q = "SELECT * FROM Friends WHERE (user_id = (SELECT id FROM Users WHERE pseudo = '"+authClients.key(sock).toStdString()+"') AND friend_id = (SELECT id FROM Users WHERE pseudo = '"+m.getContent().toStdString()+"')) OR (user_id = (SELECT id FROM Users WHERE pseudo = '"+m.getContent().toStdString()+"') AND friend_id = (SELECT id FROM Users WHERE pseudo = '"+authClients.key(sock).toStdString()+"'));";
		db.setQuery(QString(q.c_str()));
		rep = db.exec(1);
		if(rep == 1){ // s'ils sont amis on revoi une erreur.
			QString msg("ADDF:1");
			sendMsg(msg, sock);
			return;
		}
		// tout va bien, les deux personnes ne sont pas amis, on les inscrit mnt dans la base Friends
		q = "INSERT INTO Friends(Id, user_id, friend_id) VALUEs ('',(SELECT id FROM Users WHERE pseudo = '"+authClients.key(sock).toStdString()+"'), (SELECT id FROM Users WHERE pseudo = '"+m.getContent().toStdString()+"')); INSERT INTO Friends(Id, user_id, friend_id) VALUEs ('',(SELECT id FROM Users WHERE pseudo = '"+m.getContent().toStdString()+"'), (SELECT id FROM Users WHERE pseudo = '"+authClients.key(sock).toStdString()+"'));";
		db.setQuery(QString(q.c_str()));
		db.exec();
		QString msg("ADDF:0");
		sendMsg(msg, sock);
	}
} 
