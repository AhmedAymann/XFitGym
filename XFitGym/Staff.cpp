#include "User.h"
#include "Staff.h"

Staff::Staff(int id, string email, string name, string password, string phone, string role)
    : User(id, email, name, password, phone) 
{
    this->role = role;
}