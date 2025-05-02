#include "User.h"
#include "Customer.h"

Customer::Customer(int id, string email, string name, string password, string phone, char gender, int age)
    : User(id, email, name, password, phone) 
{
    this->gender = gender;
    this->age = age;
}
