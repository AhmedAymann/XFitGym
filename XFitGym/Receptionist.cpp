#include "Receptionist.h"

Receptionist::Receptionist(int id, string email, string name, string password, string phone,string role, int desknumber, int newsId, string newsText, Customer customer)
    : Staff(id, email, name, password, phone, role), 
    customer(customer) 
{
    this->desknumber = desknumber;
    this->newsId = newsId;
    this->newsText = newsText;
}