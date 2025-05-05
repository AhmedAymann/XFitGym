#pragma once
#include "User.h"
#include "Subscription.h"
#include"TrainingSession.h"
#include<qstring.h>
#include<queue>
class Customer : public User 
{
private:
	queue<TrainingSession> bookedsessions;
	//queue<Court> bookedcourt;
public: 
	
	Subscription sub;

	Customer();
	Customer(QString id, QString email, QString name,QString DateOFBirth);
	void BookPaddleCourt(int courtId, string date, string time);
	void BookTrainingSession(int sessionId);
	void CancelPaddleCourt(int courtId);
	void CancelTrainingSession(int sessionId);
	void ReschedulePaddlecourt(int courtId, string newDate, string newTime);
	void GiveFeedback(QString feedbackText);
	void CancelSubscription();

};

