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
    Cards(QString title, QString line1, QString line2, QWidget* parent = nullptr);
    //for classes
    Cards(QString title, QString line1, QString line2, int attendees, int max, QWidget* parent = nullptr);
    QHBoxLayout* buttonLayout;

private:
    QLabel* titleLabel;
    QLabel* line1Label;
    QLabel* line2Label;
};