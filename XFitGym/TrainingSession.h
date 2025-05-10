#pragma once
#include"Coach.h"
#include "qdatetime.h"


class TrainingSession
{
public:
	string name;
	int capacity;
	int size;
	int id;
	QString coachname;
	QDate date;
	QString time;

	deque<int> WaitlistIds;
};

