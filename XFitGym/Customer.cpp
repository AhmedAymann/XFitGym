#include "User.h"
#include "Customer.h"
#include "Feedback.h"
#include "Login.h"
#include "Notifications.h"
#include "Classes.h"
#include<qtimer.h>



Customer::Customer()
{
}

Customer::Customer(QString id, QString email, QString name, QString DateOFBirth)
    : User(id, email, name,  DateOFBirth)
{
  
}

void Customer::GiveFeedback(QString feedbackText)
{
    Feedback::FeedBack.push(feedbackText);
    
}



void Customer::AddCourtBooking(const QString& date, const QString& time) {

    QMap<QString, int> dayMap = {
       {"Mon", Qt::Monday},
       {"Tue", Qt::Tuesday},
       {"Wed", Qt::Wednesday},
       {"Thu", Qt::Thursday},
       {"Fri", Qt::Friday},
       {"Sat", Qt::Saturday},
       {"Sun", Qt::Sunday}
    };

    
    if (!dayMap.contains(date)) {
        qWarning() << "Invalid day name!";
         
    }

    QDate today = QDate(2025, 1, 1);
    int todayWeekday = today.dayOfWeek();         // 1 (Mon) to 7 (Sun)
    int targetWeekday = dayMap[date];

    int daysToAdd = (targetWeekday - todayWeekday + 7) % 7;
    if (daysToAdd == 0) daysToAdd = 7; // ensure the result is AFTER today

   // return today.addDays(daysToAdd);

    bookedCourt.push_back(make_pair(today.addDays(daysToAdd), time));
}

void Customer::AddTrainingSession(TrainingSession& session) {
    bookedsessions.push(session);
    Classes::allsessions[session.id].size++;
    Classes::tempallsessions[session.id].size++;
}

void Customer::CancelPaddleCourt(QDate date, QString time)
{
    
    vector<pair<QDate, QString>>::iterator it;
    for (it = bookedCourt.begin(); it != bookedCourt.end(); ++it) {
        if (it->first == date && it->second == time) {
            qDebug() << it->first << " " << it->second;
            bookedCourt.erase(it);
            break;
       }
    }
}

void Customer::CancelTrainingSession(int sessionId)
{
    queue<TrainingSession> bookedsessions1= bookedsessions;
    queue<TrainingSession> bookedsessions2;
    bool found = true;
    while (!bookedsessions1.empty()) {
        
        TrainingSession tr;
        tr = bookedsessions1.front();
        

        if (tr.id == sessionId && found) {
           
           
            if (!Classes::allsessions[sessionId].WaitlistIds.empty()) {
                Login::membersData[QString::number( Classes::allsessions[sessionId].WaitlistIds.front())].AddTrainingSession(tr);
                Notifications::notifications[Classes::allsessions[sessionId].WaitlistIds.front()].push_back("you have been added to " + tr.name + " on " + tr.date.toString("yyyy-MM-dd") + " at " + tr.time);
                Classes::allsessions[sessionId].WaitlistIds.pop_front();
                
            }
            
                Classes::allsessions[sessionId].size--;
                Classes::tempallsessions[sessionId].size--;
            
            bookedsessions1.pop();
            found = false;
        }
        else {
            bookedsessions2.push(tr);
            bookedsessions1.pop();
        }
    }
    bookedsessions = bookedsessions2;
}
