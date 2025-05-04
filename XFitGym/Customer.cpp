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
