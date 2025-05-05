#include "Receptionist.h"

Receptionist::Receptionist(QString id, QString email, QString name, QString DateOFBirth,string role, int desknumber, int newsId, string newsText, Customer customer)
    : Staff(id, email, name, DateOFBirth, role),
    customer(customer) 
{
    this->desknumber = desknumber;
    this->newsId = newsId;
    this->newsText = newsText;
}