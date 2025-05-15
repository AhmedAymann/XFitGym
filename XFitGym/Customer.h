#pragma once
#include "User.h"
#include "Subscription.h"
#include"TrainingSession.h"
#include<qstring.h>
#include<queue>
#include <vector>
#include <Stack>
#include "ProgramClock.h"




class Customer : public User 
{	
public: 
	queue<TrainingSession> bookedsessions;
	vector <pair<QDate, QString>> bookedCourt;

	
	Subscription sub;

	vector<bool> attendance;
	bool attendanceFlag = false;
	stack<TrainingSession> historyTrainingSessions;

	
	Customer();
	Customer(QString id, QString email, QString name,QString DateOFBirth);
	void AddCourtBooking(const QString& date, const QString& time);
	void AddTrainingSession(TrainingSession& session);
	void CancelPaddleCourt(QDate date, QString time);
	void CancelTrainingSession(int sessionId);
	void GiveFeedback(QString feedbackText);

};