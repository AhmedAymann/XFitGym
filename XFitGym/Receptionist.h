#pragma once
#include "Staff.h"
#include "Login.h"
#include "Customer.h"
#include "TrainingSession.h"
class Receptionist : public Staff
{
public:

	string newsText;
	
	Receptionist();
	Receptionist(QString id, QString email, QString name, QString DateOFBirth,QString role);


	void AddMember(Customer customer);
	void RemoveMember(QString userID);
	void RenewSubscription(QDate& end, QString newType, QString& oldType, QDate start);
	void CreateClass(int ID, TrainingSession session);
	void AddNews(QString newsText,QString photo);
};

