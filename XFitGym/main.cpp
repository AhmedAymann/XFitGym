#include "XFitGym.h"
#include "Subscription.h"
#include "Notifications.h"
#include "ProgramClock.h"
#include "Login.h"
#include "CustomerLoader.h"
#include <QCoreApplication>
#include <QTextStream>
#include <QtWidgets/QApplication>
#include <QTimer>
#include <QVector>



map<QString, Customer> customers;
ProgramClock* programClock = nullptr;
Notifications* notifier = nullptr;
int daysSimulated = 0;

void simulateDay(XFitGym& gui) {

    //Logging Attendance for All customers

    for (auto& c : customers) {
        if (c.second.id == gui.currentUserID) {
            //c.second.attendanceFlag = true;

            c.second.attendance.push_back(true);
        }
        else {
            c.second.attendance.push_back(false);
        }
       
        qDebug() << gui.currentUserID << "<-- User id in main";
    }



    QDate currentDate = programClock->GetCurrentDate();
    qDebug() << "\n📅 Simulated Date:" << currentDate.toString("yyyy-MM-dd");


    //Subscription Deadline Check for all customers
    for (auto& c : customers) {
        int daysLeft = notifier->CheckSubscriptionDeadline(c.second.sub, currentDate);
        qDebug() << "\n DAYS LEFT: " << daysLeft;
        if (daysLeft < 0) {
            if (!Notifications::notifications[c.first.toInt()].contains("Your Gym Membership Has Expired")) {
                Notifications::notifications[c.first.toInt()].push_back("Your Gym Membership Has Expired");
                qDebug() << "Notification for" << c.second.name << ": Your Gym Membership Has Expired";
            }
        }
        else if (daysLeft <= 10) {
            QString message = "You Have " + QString::number(daysLeft) + " Days Left in Your Subscription";
            Notifications::notifications[c.first.toInt()].push_back(message);
            qDebug() << "Notification for" << c.second.name << ":" << message;
        }
    }

    

    //Checking attendance for all Customers
    //Then clear the attendance to be ready for the next day
    for (auto& c : customers) {
        gui.dash->setAttendance(daysSimulated, c.second.attendance);
        //c.second.attendanceFlag = false;
    }



    //Moving to the Next Day
    programClock->Tick();
    daysSimulated++;
}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    XFitGym w;
    w.load();
    w.show();


    
    customers = CustomerLoader::LoadCustomersFromFile("CustomerData.txt");

    programClock = new ProgramClock(); 
    notifier = new Notifications();

    QTimer* timer = new QTimer();

    QObject::connect(timer, &QTimer::timeout, [&]() {
        simulateDay(w);
        });
    timer->start(3000); // 3 seconds per simulated day

    return a.exec();
}