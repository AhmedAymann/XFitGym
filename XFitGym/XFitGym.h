#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_XFitGym.h"
#include "Login.h"
#include "Dashboard.h"
#include "Homepage.h"
#include "userProfile.h"
#include "notifications.h"
#include "feedback.h"
#include <QString>
#include <QScrollBar>
#include "qtimer.h"


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

    XFitGym(QWidget *parent = nullptr);
    ~XFitGym();

    void setScrolltoTop();
private:
    Ui::XFitGymClass ui;
};
