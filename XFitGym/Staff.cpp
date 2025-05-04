#include "User.h"
#include "Staff.h"

Staff::Staff(QString id, QString email, QString name,QString DateOFBirth, string role)
    : User(id, email, name, DateOFBirth)
{
    this->role = role;
}