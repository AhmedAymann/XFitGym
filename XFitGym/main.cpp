#include "XFitGym.h"
#include "Subscription.h"
#include "Notifications.h"
#include "ProgramClock.h"
#include "Login.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XFitGym w;
    w.load();
    w.show();


    QVector<Customer> customers = loaddata("customers.txt");


    ProgramClock clock;
    Notifications notifier;




    //CHECKING FOR ONLY ONE PERSON'S SUBSCRIPTION



    // Simulate 20 days passing
    for (int day = 0; day < 20; day++)
    {
        qDebug() << "\n📅 Current Program Date:" << clock.GetCurrentDate().toString("yyyy-MM-dd");

        // Check subscription deadline based on program time
        notifier.CheckSubscriptionDeadline(sub, clock.GetCurrentDate());

        // Advance to next day
        clock.Tick();
    }








    return a.exec();
    //khalx
}
