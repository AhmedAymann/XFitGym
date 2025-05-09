#include "XFitGym.h"
#include "Subscription.h"
#include "Notifications.h"
#include "ProgramClock.h"
#include "Login.h"
#include "CustomerLoader.h"
#include <QCoreApplication>
#include <QTextStream>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XFitGym w;
    w.load();
    w.show();

    QVector<Customer> customers = CustomerLoader::LoadCustomersFromFile("customers.txt");


    ProgramClock clock;
    Notifications notifier;


    // Simulate 20 days passing
    for (int day = 0; day < 20; day++)
    {
        QDate currentDate = clock.GetCurrentDate();
        qDebug() << "\n📅 Simulated Date:" << currentDate.toString("yyyy-MM-dd");


        // Checks for the subscriptions of all of the customers

        int notificationFlag = -1;
        for (const Customer& c : customers)
        {
             int daysLeft = notifier.CheckSubscriptionDeadline(c.sub, currentDate);
             
             if (daysLeft < 0) {
                 notificationFlag = 1;
                 Notifications::notifications[c.id.toInt()].push_back("Your Gym Membership Has Expired");
             }
             else if (daysLeft <= 10) {
                 notificationFlag = 2;
                 Notifications::notifications[c.id.toInt()].push_back("You Have " + QString::number(daysLeft) + " Days Left in Your Subscription");
             }
        }

        // Advance to next day
        clock.Tick();
    }

    return a.exec();
    //khalx
}
