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

    static bool half;
    static bool quarter;
    static bool tenth;

    Subscription();
    Subscription(QString type);
    double CalculatePrice(double priceBeforeDiscount, QDate currentDate, QDate endDate, QString type);
    void SetStartDate(QDate currentDate);
    void SetEndDate(QDate end);
};

