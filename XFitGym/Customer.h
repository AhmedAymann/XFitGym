#pragma once
#include "User.h"
#include "Subscription.h"
#include"TrainingSession.h"
#include<qstring.h>
#include<queue>
#include <vector>




class Customer : public User 
{	
public: 
	queue<TrainingSession> bookedsessions;
	vector <pair<QDate, QString>> bookedCourt;
	
	Subscription sub;

	vector<bool> attendance;
	bool attendanceFlag = false;

	
	Customer();
	Customer(QString id, QString email, QString name,QString DateOFBirth);
	void AddCourtBooking(const QDate& date, const QString& time);
	void AddTrainingSession(TrainingSession& session);
	void CancelPaddleCourt(int courtId);
	void CancelTrainingSession(int sessionId);
	void ReschedulePaddlecourt(int courtId, string newDate, string newTime);
	void GiveFeedback(QString feedbackText);
	void CancelSubscription();

};

