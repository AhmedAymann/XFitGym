#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_notifications.h"
#include "Subscription.h"
#include <QDate>

class Notifications : public QWidget
{
    Q_OBJECT

public:
    Notifications(QWidget* parent = nullptr);
    ~Notifications();
    Ui::NotificationsClass ui;



    void CheckSubscriptionDeadline(const Subscription& subscription, const QDate& currentDate);



};