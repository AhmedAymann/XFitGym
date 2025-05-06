#include "Notifications.h"


Notifications::Notifications(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);

}
Notifications::~Notifications()
{}


void Notifications::CheckSubscriptionDeadline(const Subscription& subscription, const QDate& currentDate)
{
    QDate end = QDate::fromString(subscription.endDate, "yyyy-MM-dd");

    if (!end.isValid()) {
        qDebug() << "Invalid end date!";
        return;
    }

    int daysRemaining = currentDate.daysTo(end);

    if (daysRemaining <= 10 && daysRemaining >= 0) {
        //add the notification to the proper user using Gui
        qDebug() << " Subscription for type:" << subscription.type
            << "will end in" << daysRemaining << "days!";
    }
}