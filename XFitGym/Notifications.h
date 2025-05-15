#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_notifications.h"
#include "Subscription.h"
#include "Customer.h"
#include <QDate>
#include <Stack>


class Notifications : public QWidget
{
    Q_OBJECT

public:
    Notifications(QWidget* parent = nullptr);
    ~Notifications();
    Ui::NotificationsClass ui;

    static QMap<int, QVector<QString>> notifications;
    static QMap<int, QVector<QString>> tempNotifications;
    void saveNotifications();
    void loadNotifications();

    int CheckSubscriptionDeadline(const Subscription& subscription, const QDate& currentDate);

};