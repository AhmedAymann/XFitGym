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


        for (const Customer& c : customers)
        {
            notifier.CheckSubscriptionDeadline(c.sub, currentDate);
        }

        // Advance to next day
        clock.Tick();
    }

    return a.exec();
    //khalx
}
