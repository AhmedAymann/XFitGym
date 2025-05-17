#pragma once

#include "Staff.h"
#include "Customer.h"
#include "Coach.h"
#include "Receptionist.h"
#include<stack>
class Manager : public Staff
{
public:
	
	static int monthlyCounter ;
	static int sixmonthlyCounter ;
	static int yearlyCounter ;
	static int yearlyVIPCounter ;

	

	static int sessionsCounter;
	static int courtsCounter;

	

	Manager(QString id, QString email, QString name, QString DateOFBirth, QString role);

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

