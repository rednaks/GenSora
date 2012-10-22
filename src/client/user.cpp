#include "user.h"

User::User(std::string n, std::string pr, std::string e, std::string ps, std::string pass){
	nom = n;
	prenom = pr;
	email = e;
	pseudo = ps;
	password = pass;

}

// set & get
        void setNom(std::string a){
	nom = a;
}
        void getNom(){
	return nom;
}
        void setPrenom(string a){
	prenom = a;
}
        void getPrenom(){
	return prenom;
}
        void setEmail(string a){
	email = a;
}
        void getEmail(){
	return email;
}
        void setPseudo(string a){
	pseudo = a;
}
        void getPseudo(){
	return pseudo;
}
        void setPassword(string a){
	password = a;
}
        void getPassword(){
	return password;
}
User::~User(){
}
