#include "Receptionist.h"

map<QString, Receptionist> Receptionist::recepData;

Receptionist::Receptionist()
{}

Receptionist::Receptionist(QString id, QString email, QString name, QString DateOFBirth, QString role, string newsText)
    : Staff(id, email, name, DateOFBirth, role)
{

}

void Receptionist::AddMember(Customer customer)
{
    
}
void Receptionist::RemoveMember(int userID)
{

}
void Receptionist::RenewSubscription(int userID, int Startdate)
{

}
