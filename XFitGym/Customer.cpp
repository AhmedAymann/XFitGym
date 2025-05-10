#include "User.h"
#include "Customer.h"
#include "Feedback.h"



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