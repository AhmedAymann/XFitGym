#pragma once

#include "Staff.h"
#include "Customer.h"
#include "Coach.h"
#include "Receptionist.h"
#include<stack>
class Manager : public Staff
{
public:
	

	Manager(QString id, QString email, QString name, QString DateOFBirth, string role);

	void AddMember(Customer customer);
	void RemoveMember(int userID);
	void RenewSubscription(int userID, int Startdate);
	void UpdateSubscription(int userId);
	void CancelSubscription(int userId);

	void AddCoach(Coach coach);
	void RemoveCoach(int coachId);

	void AddReceptionist(Receptionist receptionist);
	void RemoveReceptionist(int receptionistId);

	
};

