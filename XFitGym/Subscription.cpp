#include "Subscription.h"
#include <QDate>
#include <QString>
#include <Manager.h>


Subscription::Subscription() {
   
}
Subscription::Subscription(QString type) {
    this->type = type;
}

bool Subscription::half = false;
bool Subscription::quarter = false;
bool Subscription::tenth = false;

void Subscription::SetStartDate(QDate currentDate)
{
    startDate = currentDate.toString("yyyy-MM-dd");
}
void Subscription::SetEndDate(QDate end)
{
    endDate = end;
}
double Subscription::CalculatePrice(double priceBeforeDiscount, QDate currentDate, QDate endDate, QString type)
{

    QDate start;
    double progress;
    int daysPassed = 0;
    int totalDays = 0;

    if (type.toLower() == "monthly") {
        totalDays = 30;
        start = endDate.addMonths(-1);
        daysPassed = start.daysTo(currentDate);

    }
    else if (type.toLower() == "6-months") {
        totalDays = 180;
        start = endDate.addMonths(-6);
        daysPassed = start.daysTo(currentDate);
    }
    else if (type.toLower() == "yearly") {
        totalDays = 365;
        start = endDate.addYears(-1);
        daysPassed = start.daysTo(currentDate);
    }
    else if (type.toLower() == "yearly vip") {
        totalDays = 365;
        start = endDate.addYears(-1);
        daysPassed = start.daysTo(currentDate);
    }    

    if (daysPassed <= 0) daysPassed = 0;
    if (totalDays == 0) progress = 0;
    else progress = (double)daysPassed / totalDays;

    qDebug() << progress;

    if (progress == 0) {
        return 0;
    }
    else if (progress <= 0.25)
    {
        half = true;
        quarter = false;
        tenth = false;
        return priceBeforeDiscount * 0.5;
    }
    else if (progress <= 0.5)
    {
        quarter = true;
        half = false;
        tenth = false;
        return priceBeforeDiscount * 0.25;
    }
    else if (progress <= 0.75)
    {
        tenth = true;
        half = false;
        quarter = false;
        return priceBeforeDiscount * 0.1;
    }
    else
        return 0;
}

int Subscription::monthlyCounter = 0;
int Subscription::sixmonthlyCounter = 0;
int Subscription::yearlyCounter = 0;
int Subscription::yearlyVIPCounter = 0;
