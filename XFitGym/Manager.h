#pragma once

#include "Staff.h"
#include "Customer.h"
#include "Coach.h"
#include "Receptionist.h"
#include<stack>
class Manager : public Staff
{
public:
	static int discountHalfCounter;
	static int discountQuarterCounter;
	static int discountTenthCounter;
	static double totalSubFees;

	double coachSal = 200;
	double recepSal = 150;

	double classFees = 75;
	double courtFees = 75;

	double monthFee = 300;
	double sixmonthFee = 1200;
	double yearFee = 2200;
	double VIPFee = 4000;



	Manager();
	Manager(QString id, QString email, QString name, QString DateOFBirth, QString role);

	void AddMember(Customer customer);
	void RemoveMember(QString userID);
	void RenewSubscription(QDate& end, QString newType, QString& oldType, QDate start);
	void AddCoach(Coach coach);
	void RemoveStaff(QString coachId);
	void AddReceptionist(Receptionist receptionist);

	
};

