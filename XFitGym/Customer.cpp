#include "User.h"
#include "Customer.h"
#include "Feedback.h"
#include "Login.h"
#include "Notifications.h"
#include "Classes.h"



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

void Customer::AddCourtBooking(const QDate& date, const QString& time) {
    bookedCourt.push_back(make_pair(date, time));
}

void Customer::AddTrainingSession(TrainingSession& session) {
    bookedsessions.push(session);
    Classes::allsessions[session.id].size++;
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
                Classes::allsessions[sessionId].size--;
            }
            else {
                Classes::allsessions[sessionId].size--;
            }
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
