#pragma once
#include "User.h"
class Staff : public User
{
public:
	string role;

	Staff(int id, string email, string name, string password, string phone, string role);

};

