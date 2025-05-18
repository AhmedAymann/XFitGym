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
    static bool notSubscribed;

    Subscription();
    Subscription(QString type);
    void confirmRenew(QDate& end, QString newType, QString& oldType, QDate start);
    double CalculatePrice(double priceBeforeDiscount, QDate currentDate, QDate endDate, QString type);
    void SetStartDate(QDate currentDate);
    void SetEndDate(QDate end);
};

