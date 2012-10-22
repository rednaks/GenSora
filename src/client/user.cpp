#include "user.h"

User::User(std::string n, std::string pr, std::string e, std::string ps, std::string pass){
	nom = n;
	prenom = pr;
	email = e;
	pseudo = ps;
	password = pass;

}
User::User(){
nom = "";
prenom = "";
email = "";
pseudo = "";
password = "";
}

// set & get
        void User::setNom(std::string a){
	nom = a;
}
        std::string User::getNom(){
	return nom;
}
        void User::setPrenom(std::string a){
	prenom = a;
}
        std::string User::getPrenom(){
	return prenom;
}
        void User::setEmail(std::string a){
	email = a;
}
        std::string User::getEmail(){
	return email;
}
        void User::setPseudo(std::string a){
	pseudo = a;
}
        std::string User::getPseudo(){
	return pseudo;
}
        void User::setPassword(std::string a){
	password = a;
}
        std::string User::getPassword(){
	return password;
}
User::~User(){
}

