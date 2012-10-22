#ifndef USER_H
#define USER_H
#include <string>



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
#endif
