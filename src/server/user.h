#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <QString>
#include <sstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>



class User{
	

private:
	 std::string nom;
	 std::string prenom;
	 std::string email;
	 std::string pseudo;
	 std::string password;
public:
	User(std::string n, std::string pr, std::string e, std::string ps, std::string pass);
	~User();
	User();
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version){
		ar & pseudo;
		ar & prenom;
		ar & nom;
		ar & password;
		ar & email;
	}
	void setNom(std::string a);
	std::string getNom();
 	void setPrenom(std::string a);
        std::string getPrenom();
	void setEmail(std::string a);
        std::string getEmail();
	void setPseudo(std::string a);
        std::string getPseudo();
	void setPassword(std::string a);
        std::string getPassword();
};

class FriendList{
public:
	FriendList();
	int size();
	std::string operator[](int);
	void operator<<(QString);
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version){
		ar & list;
	}

private:
	std::vector<std::string> list;

};
#endif
