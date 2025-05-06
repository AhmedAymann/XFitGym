#include "Subscription.h"
#include <QDate>
#include <QString>


Subscription::Subscription() {
   
}

Subscription::Subscription(QString type) {
    this->type = type;
}


void Subscription::SetStartDate()
{
    QDate currentDate = QDate::currentDate();
    startDate = currentDate.toString("yyyy-MM-dd");
}

void Subscription::SetEndDate(int durationDays)
{
    QDate currentDate = QDate::currentDate();
    endDate = currentDate.addDays(durationDays).toString("yyyy-MM-dd");
}


int Subscription::CalculatePrice(int priceBeforeDiscount, const QString& currentDate)
{
    QDate start = QDate::fromString(startDate, "yyyy-MM-dd");
    QDate end = QDate::fromString(endDate, "yyyy-MM-dd");
    QDate current = QDate::fromString(currentDate, "yyyy-MM-dd");

    int totalDays = start.daysTo(end);
    int daysPassed = start.daysTo(current);

    double progress = (double)daysPassed / totalDays;

    if (progress < 0.5)
        return priceBeforeDiscount * 0.5;
    else if (progress < 0.75)
        return priceBeforeDiscount * 0.8;
    else
        return priceBeforeDiscount;
}

