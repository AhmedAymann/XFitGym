#pragma once
#include"Coach.h"
#include "qdatetime.h"


class TrainingSession
{
public:
	string name;
	int capacity;
	int id;
	QString coachname;
	QDate date;
	QString time;

	vector<int> WaitlistIds;



};

