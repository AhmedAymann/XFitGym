#pragma once
#include "User.h"
class Customer : public User 
{
private:
	//queue<TrainingSession> bookedsessions;
	//queue<Court> bookedcourt;
public: 
	char gender;
	int age;
	//Subscription sub;

	Customer(int id, string email, string name, string password, string phone, char gender, int age);
	void BookPaddleCourt(int courtId, string date, string time);
	void BookTrainingSession(int sessionId);
	void CancelPaddleCourt(int courtId);
	void CancelTrainingSession(int sessionId);
	void ReschedulePaddlecourt(int courtId, string newDate, string newTime);
	void GiveFeedback(int sessionId, string feedbackText, int rating);

};

