#pragma once
#include <QString>
#include <QDateTime>


class Subscription
{
public:

    static int monthlyCounter;
    static int sixmonthlyCounter;
    static int yearlyCounter;
    static int yearlyVIPCounter;

    QString type;
    QString startDate; 
    QDate endDate;
    int priceAfterDiscount;

    Subscription();
    Subscription(QString type);
    int CalculatePrice(int priceBeforeDiscount, const QString& currentDate);
    void SetStartDate();  
    void SetEndDate(int durationDays); 
};

