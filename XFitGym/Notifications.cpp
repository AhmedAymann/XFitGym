#include "Notifications.h"
#include <QFile>
#include <QTextStream>


Notifications::Notifications(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);

}
Notifications::~Notifications()
{}

QMap<int, QVector<QString>> Notifications::notifications;
QMap<int, QVector<QString>> Notifications::tempNotifications;

int Notifications::CheckSubscriptionDeadline(const Subscription& sub, const QDate& currentDate)
{
    // If there's no subscription -> skip check
    if (sub.type == "NoSubscription") {
        return -3;
    }
    

    // Parse endDate from QString to QDate
    QDate endDate = QDate::fromString(sub.endDate, "yyyy-MM-dd");

    
     if (!endDate.isValid()) {
        qWarning() << "❌ Invalid subscription end date format for customer:" << sub.endDate;
        return -2;  // Return early in case of an invalid date format
    }


    //SATR EL MINUS
    int daysLeft = currentDate.daysTo(endDate);
    return daysLeft;


    if (daysLeft < 0) {
        //SEND A NOTIFICATION SAYING THAT THE SUBSCRIPTION HAD ENDED
        qDebug() << "⚠️ Subscription has already expired on" << endDate.toString("yyyy-MM-dd");
    }
    else if (daysLeft <= 10) {
        //SEND A NOTIFICATION SAYING THAT YOUR SUBSCRIPTION IS EXPIRING IN N DAYS
        qDebug() << "⏳ Subscription is expiring in" << daysLeft << "day(s) on" << endDate.toString("yyyy-MM-dd");
    }
}




// Load and Save Functiona (We decided To remove them at the end)


void Notifications::saveNotifications()
{


    QFile file("Notifications.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "Failed to clear file:" << file.errorString();

    }
    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        qDebug() << "Cannot open file:" << file.errorString();

    }

    QTextStream out(&file);

    for (auto it = tempNotifications.begin(); it != tempNotifications.end(); ++it) {
        int id = it.key();
        const QVector<QString>& messages = it.value();
        for (const QString& msg : messages) {
            out << id << "," << msg << "\n";
        }
    }



    file.close();

}




void Notifications::loadNotifications()
{
    QFile file("Notifications.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file:" << file.errorString();

    }
    QTextStream in(&file);
  

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        notifications[parts[0].toInt()].push_back(parts[1]);
    }

    tempNotifications = notifications;
    file.close();
}
