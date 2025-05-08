#include "Notifications.h"


Notifications::Notifications(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);

}
Notifications::~Notifications()
{}

void Notifications::CheckSubscriptionDeadline(const Subscription& sub, const QDate& currentDate)
{
    // If there's no subscription -> skip check
    if (sub.type == "No Subscription") {
        return;
    }

    // Parse endDate from QString to QDate
    QDate endDate = QDate::fromString(sub.endDate, "dd/MM/yyyy");
    if (!endDate.isValid()) {
        qWarning() << "❌ Invalid subscription end date format for customer.";
        return;
    }

    //SATR EL MINUS
    int daysLeft = currentDate.daysTo(endDate);

    if (daysLeft < 0) {
        //SEND A NOTIFICATION SAYING THAT THE SUBSCRIPTION HAD ENDED
        qDebug() << "⚠️ Subscription has already expired on" << endDate.toString("yyyy-MM-dd");
    }
    else if (daysLeft <= 3) {
        //SEND A NOTIFICATION SAYING THAT YOUR SUBSCRIPTION IS EXPIRING IN N DAYS
        qDebug() << "⏳ Subscription is expiring in" << daysLeft << "day(s) on" << endDate.toString("yyyy-MM-dd");
    }
}


