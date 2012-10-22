#ifndef USER_H
#define USER_H
#include <string>



class User: public QObject {
	Q_OBJECT

private:
	 std::string nom;
	 std::string prenom;
	 std::string email;
	 std::string pseudo;
	 std::string password;
public:
	User();
	void setNom(string a);
	void getNom();
 	void setPrenom(string a);
        void getPrenom();
	void setEmail(string a);
        void getEmail();
	void setPseudo(string a);
        void getPseudo();
	void setPassword(string a);
        void getPassword();
};
#endif
