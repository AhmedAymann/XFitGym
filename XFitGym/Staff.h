#pragma once
#include "User.h"
class Staff : public User
{
public:
	string role;

	Staff(QString id, QString email, QString name, QString DateOFBirth, string role);

};

