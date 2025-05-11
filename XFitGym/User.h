#pragma once
#include<iostream>
#include<QString.h>
using namespace std;

class User {
public:

	QString id;
	QString email;
	QString name;
	QString DateOFBirth;
	
	User();
	User(QString id,QString email,QString name, QString DateOFBirth);

};