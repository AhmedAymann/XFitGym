#pragma once
#include <string>
#include<QString>

using namespace std;


class Subscription
{
public:
	QString name;
	string startDate;
	string endDate;
	int price;

	Subscription();
	Subscription(QString name, string startDate);
	
};

