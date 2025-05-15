#pragma once
#include "Staff.h"
#include "Customer.h"
#include "TrainingSession.h"
class Receptionist : public Staff
{
public:

	static map<QString, Receptionist> recepData;
	string newsText;
	
	Receptionist();
	Receptionist(QString id, QString email, QString name, QString DateOFBirth,QString role, string newsText);

	void AddMember(Customer customer);
	void RemoveMember(int userID);
	void RenewSubscription(int userID, int Startdate);
	void CreateClass(TrainingSession session);
	void DeleteClass(int classId);
	void AddNews(QString newsText,QString photo);
};

