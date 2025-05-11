#include "TrainingSession.h"

TrainingSession::TrainingSession()
{
}

TrainingSession::TrainingSession(int id, QString name, int capacity, int size, QString coachname, QDate date, QString time)
{
	this->id = id;
	this->name = name;
	this->capacity = capacity;
	this->size = size;
	this->coachname = coachname;
	this->date = date;
	this->time = time;
}
