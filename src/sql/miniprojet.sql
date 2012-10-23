create database MiniProjetCpp;
use MiniProjetCpp;
create table Users(Id int auto_increment, nom varchar(255) NOT NULL, prenom varchar(255) NOT NULL, email varchar(255) NOT NULL, mdp varchar(32) NOT NULL, pseudo varchar(50) UNIQUE, etat ENUM('0','1','2'), PRIMARY KEY(Id,pseudo));

create table Friends(Id int auto_increment , user_id int , friend_id int , etat ENUM('0','1','2') , PRIMARY KEY(Id) , FOREIGN KEY(user_id)REFERENCES Users(Id), FOREIGN KEY(friend_id)REFERENCES Users(Id));

create table Admin(Id int auto_increment , u_id int , PRIMARY KEY(Id) , FOREIGN KEY(u_id)REFERENCES Users(Id));

create table Offline_msg(Id int auto_increment , sender_id int , receiver_id int , msg text NOT NULL , date DATETIME , etat BOOL , PRIMARY KEY(Id) , FOREIGN KEY(sender_id)REFERENCES Users(Id) , FOREIGN KEY(receiver_id)REFERENCES Users(Id));

create table Requests(Id int auto_increment , u_id int , a_id int , request text NOT NULL , etat BOOL , date DATETIME , primary key(Id) , foreign key(u_id)REFERENCES Users(Id) , foreign key(a_id)REFERENCES Users(Id));

