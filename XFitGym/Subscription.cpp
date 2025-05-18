#include "Subscription.h"
#include <QDate>
#include <QString>


Subscription::Subscription() {
   
}
Subscription::Subscription(QString type) {
    this->type = type;
}

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

    if (type.toLower() == "monthly") {

    }
    else if (type.toLower() == "monthly") {

    }
    else if (type.toLower() == "monthly") {

    }
    else if (type.toLower() == "monthly") {

    }
    QDate start = QDate::fromString(startDate, "yyyy-MM-dd");
    
    int totalDays = start.daysTo(endDate);
    int daysPassed = start.daysTo(currentDate);

    double progress = (double)daysPassed / totalDays;

    if (progress < 0.25)
        return priceBeforeDiscount * 0.5;
    else if (progress < 0.5)
        return priceBeforeDiscount * 0.25;
    else if (progress < 0.75)
        return priceBeforeDiscount * 0.1;
    else
        return priceBeforeDiscount;
}


int Subscription::monthlyCounter = 0;
int Subscription::sixmonthlyCounter = 0;
int Subscription::yearlyCounter = 0;
int Subscription::yearlyVIPCounter = 0;
