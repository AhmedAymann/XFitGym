#include"User.h"

User::User()
{
}

User::User(QString id, QString email, QString name, QString DateOFBirth)
{
	this->id = id;
	this->email = email;
	this->name = name;
	this->DateOFBirth = DateOFBirth;
	
}
