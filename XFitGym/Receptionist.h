#pragma once
#include "Staff.h"
#include "Customer.h"

class Receptionist : public Staff
{
public:
	int desknumber;
	int newsId;
	string newsText;
	Customer customer;

	Receptionist(int id, string email, string name, string password, string phone,string role, int desknumber, int newsId, string newsText, Customer customer);


	void AddMember(Customer customer);
	void RemoveMember(int userID);
	void RenewSubscription(int userID, int Startdate);
	void UpdateSubscription(int userId);
	void CancelSubscription(int userId);
	//void CreateClass(TrainingSession class);
	void DeleteClass(int classId);
	void AddNews(int newsId, string newsText);
};

