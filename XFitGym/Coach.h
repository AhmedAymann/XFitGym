#pragma once
#include "Staff.h"
#include "Classes.h"
#include<stack>
class Coach : public Staff
{
	Coach();
	Coach(QString id, QString email, QString name, QString DateOFBirth, QString role);
public:
	void CancelSession(int id);
};

