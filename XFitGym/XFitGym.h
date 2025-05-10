#pragma once

#include <QtWidgets/QMainWindow>
#include <QString>
#include <QScrollBar>
#include "qtimer.h"
#include "ui_XFitGym.h"
#include "Login.h"
#include "Dashboard.h"
#include "Manager.h"
#include "Homepage.h"
#include "userProfile.h"
#include "classes.h"
#include "notifications.h"
#include "feedback.h"
#include "Padel.h"
#include "Manager_homepage.h"
#include "Manager_dashboard.h"
#include "Manager_members.h"
#include "Manager_staff.h"
#include "Manager_tournaments.h"
#include "Manager_feedback.h"


class XFitGym : public QMainWindow
{
    Q_OBJECT

public:

Login* log;
Dashboard* dash;
Gauge* Pgauge;
Gauge* Cgauge;
Homepage* home;
userProfile* user_Profile;
Notifications* notifications;
Feedback* feedback;
Classes* classes;
Padel* padel;
Manager_homepage* man_home;
Manager_dashboard* man_dash;
Manager_members* man_members;
Manager_staff* man_staff;
Manager_tournaments* man_tournaments;
Manager_feedback* man_feedback;

    XFitGym(QWidget *parent = nullptr);
    ~XFitGym();

    void setScrolltoTop();
    void save();
    void load();
private:
    Ui::XFitGymClass ui;
};



class Cards : public QWidget {
    Q_OBJECT
public:
    //for staff and members
    Cards(QString title, QString line1, QString line2, QWidget* parent = nullptr);
    //for classes
    Cards(QString title, QString line1, QString line2, int attendees, int max, QWidget* parent = nullptr);

    QHBoxLayout* buttonLayout;

private:
    QLabel* titleLabel;
    QLabel* line1Label;
    QLabel* line2Label;
};