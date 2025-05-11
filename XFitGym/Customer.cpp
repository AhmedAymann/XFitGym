#include "User.h"
#include "Customer.h"
#include "Feedback.h"
#include "Login.h"



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

void Customer::AddTrainingSession(const TrainingSession& session) {
    bookedsessions.push(session);
}


void Customer::CancelTrainingSession(int sessionId)
{
    queue<TrainingSession> bookedsessions1 = bookedsessions;
    queue<TrainingSession> bookedsessions2;

    while (!bookedsessions1.empty()) {
        TrainingSession tr;
        tr = bookedsessions1.front();

        if (tr.id == sessionId) {
            if (!tr.WaitlistIds.empty()) {
                Login::membersData[QString::number(tr.WaitlistIds.front())].AddTrainingSession(tr);
                tr.WaitlistIds.pop_front();
            }
            else {
                tr.size--;
            }
            bookedsessions1.pop();
        }
        else {
            bookedsessions2.push(tr);
            bookedsessions1.pop();
        }
    }
    bookedsessions = bookedsessions2;
}


