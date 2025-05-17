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
    // Logging Attendance for All customers
    for (auto& c : Login::membersData) {
        //qDebug() << "Customer of id" << c.second.id << " - gui.currentUserID " << gui.currentUserID;

        // Mark attendance as true for the logged-in customer, false for others
        if (c.second.id == gui.currentUserID) {
            c.second.attendance.push_back(true);  // Attendance is true for logged-in user
            qDebug() << "Attendance True for " << c.second.name;
        }
        else {
            c.second.attendance.push_back(false);  // Attendance is false for others
            qDebug() << "Attendance False for " << c.second.name;
        }

        // Make sure attendance is updated for each customer in the vector
        //qDebug() << "Attendance for " << c.second.name << ": " << c.second.attendance.back();

        //qDebug() << "Day: " << daysSimulated << ", Attendance: " << c.second.attendance;
    }

    // Log current date for simulation
    QDate currentDate = programClock->GetCurrentDate();
    qDebug() << "\n📅 Simulated Date:" << currentDate.toString("yyyy-MM-dd");

    // Subscription Deadline Check for all customers
    for (auto& c : Login::membersData) {
        int daysLeft = notifier->CheckSubscriptionDeadline(c.second.sub, currentDate);
        //qDebug() << "\n DAYS LEFT: " << daysLeft;
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



    //// Check if Each bookedcourts of each customer is due in 3 days or not 
    //for (auto& c : Login::membersData) {
    //    for (auto a : c.second.bookedCourt) {
    //        int daysLeftCancelCourts = currentDate.daysTo(a.first);
    //        if (daysLeftCancelCourts <= 3) {
    //            // Find the button that matches this booking
    //            for (CourtWidgetData& data : gui.allCourtButtons) {
    //                if (data.bookingDate == a.first && data.timeSlot == a.second) {
    //                    data.cancelButton->setEnabled(false);
    //                    data.cancelButton->setStyleSheet(" QPushButton { background-color: grey; border: 1px solid grey; }");
    //                }
    //            }
    //        }
    //    }
    //}
    //


    ////Check for all Training Sessions if Their date had passed
    for (auto it = Classes::allsessions.begin(); it != Classes::allsessions.end(); ) {
        int daysLeftSessions = currentDate.daysTo(it->second.date);
        if (it->second.id == 200) {
            qDebug() << "daysLeftSessions " << "For Class: " << it->second.id << "is: " << daysLeftSessions;
        }
        if (daysLeftSessions < 0) {
            it = Classes::allsessions.erase(it);  // safe erase
        }
        else {
            ++it;
        }
    }
    

    

    //Check if a Training Session had passed and put it in the History
    for (auto& c : Login::membersData) {
        int sz = Login::membersData[c.first].bookedsessions.size();
        if (sz == 0) continue;
        //if (c.first == "199") {
        //qDebug() << "SZ IS : " << sz;
        //qDebug() << "Booked session id " << Login::membersData[c.first].bookedsessions.front().id;
        //}
        for (int i = 0; i < sz; i++) {
            int daysLeftHistoryCourts = currentDate.daysTo(Login::membersData[c.first].bookedsessions.front().date);
            //qDebug() << "daysLeftHistoryCourts " << "of customer " << c.second.name << " is ";
            TrainingSession tp = Login::membersData[c.first].bookedsessions.front();
            if (daysLeftHistoryCourts < 0) {
                //qDebug() << "TrainingSession: " << tp.id << "PASSED x 1";
                Login::membersData[c.first].historyTrainingSessions.push(tp);
                //qDebug() << "TrainingSession: " << tp.id << "PASSED x 2";
                Login::membersData[c.first].bookedsessions.pop();
                //qDebug() << "TrainingSession: " << tp.id << "PASSED x 3";
                //Classes::allsessions.erase(tp.id);
            }
            else {
                //qDebug() << "TrainingSession: " << tp.id << "NOT PASS";
                Login::membersData[c.first].bookedsessions.pop();
                Login::membersData[c.first].bookedsessions.push(tp);
            }
       }
    }




    // Checking attendance for all customers and updating the GUI
    if (Login::membersData.find(gui.currentUserID) != Login::membersData.end()) {
        gui.dash->setAttendance(daysSimulated, Login::membersData[gui.currentUserID].attendance);
    }

    // Moving to the Next Day
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
    timer->start(7000); // #/1000 seconds per simulated day

    return a.exec();
}