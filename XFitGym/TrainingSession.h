#pragma once
#include "qdatetime.h"
#include <deque>
using namespace std;


class TrainingSession
{
public:
	QString name;
	int capacity;
	int size;
	int id;
	QString coachname;
	QDate date;
	QString time;

	deque<int> WaitlistIds;

	TrainingSession(); 
	TrainingSession(int id,QString name,int capacity,int size,QString coachname,QDate date,QString time);

};

