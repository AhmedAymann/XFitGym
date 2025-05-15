#pragma once
#include "Staff.h"
#include "Classes.h"
#include<stack>
class Coach : public Staff
{
public:
	Coach();
	Coach(QString id, QString email, QString name, QString DateOFBirth, QString role);
	static map<QString, Coach> coachData;
	void CancelSession(int id);
};

