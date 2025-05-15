#pragma once


#include <QtWidgets/QMainWindow>
#include <QString>
#include <set>
#include <QScrollBar>
#include <QButtonGroup>
#include <QIntValidator>
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
#include "Staff_profile.h"
#include "Coach_homepage.h"
#include "Receptionist_homepage.h"
#include "Receptionist_members.h"
#include "Receptionist_classes.h"
#include "Receptionist_news.h"
#include "CourtWidgetData.h"
#include "Staff.h"


class XFitGym : public QMainWindow
{
    Q_OBJECT

public:

vector<CourtWidgetData> allCourtButtons;
QString currentUserID;
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
renewMembers* renewPage;
addMembers* addPage;
Staff_profile* manprofile;
Staff_profile* coachprofile;
Staff_profile* recepprofile;
Coach_homepage* coach_home;
Coach_classes* coach_classes;
Receptionist_homepage* recep_home;
Receptionist_members* recep_members;
Receptionist_classes* recep_classes;
Receptionist_news* recep_news;
Staff* staff;
Coach* coach;
QMap<QPair<QString, QString>, QPushButton*> courtSlotButtons;


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