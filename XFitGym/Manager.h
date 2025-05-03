#pragma once
#include "Staff.h"
#include "Customer.h"
#include "Coach.h"
#include "Receptionist.h"
class Manager : public Staff
{
public:

	Manager(int id, string email, string name, string password, string phone, string role);

	void AddMember(Customer customer);
	void RemoveMember(int userID);
	void RenewSubscription(int userID, int Startdate);
	void UpdateSubscription(int userId);
	void CancelSubscription(int userId);

	void AddCoach(Coach coach);
	void RemoveCoach(int coachId);

	void AddReceptionist(Receptionist receptionist);
	void RemoveReceptionist(int receptionistId);

	//void AddTournament(Tournament tournament);

};

