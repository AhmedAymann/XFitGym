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

QString User::getId() const  {
    return id;
}
QString User::getEmail() const  {
    return email;
}
QString User::getName() const  {
    return name;
}
QString User::getDateOfBirth() const  {
    return DateOFBirth;
}

void User::setId(const QString& id) {
    this->id = id;
}
void User::setEmail(const QString& email) {
    this->email = email;
}
void User::setName(const QString& name) {
    this->name = name;
}
void User::setDateOfBirth(const QString& dob) {
    this->DateOFBirth = dob;
}
