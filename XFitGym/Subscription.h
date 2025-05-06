#pragma once
#include <QString>
#include <QDateTime>


class Subscription
{
public:
    QString type;
    QString startDate; 
    QString endDate;
    int priceAfterDiscount;

    Subscription();
    Subscription(QString type);
    int CalculatePrice(int priceBeforeDiscount, const QString& currentDate);
    void SetStartDate();  
    void SetEndDate(int durationDays); 
};

