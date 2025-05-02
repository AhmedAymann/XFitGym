#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_XFitGym.h"
#include "Login.h"
#include "Dashboard.h"
#include "Homepage.h"
#include "userProfile.h"
#include <QString>
#include "qtimer.h"

class XFitGym : public QMainWindow
{
    Q_OBJECT

public:
    XFitGym(QWidget *parent = nullptr);
    ~XFitGym();
    Login* log;
    Dashboard* dash;
    Gauge* Pgauge;
    Gauge* Cgauge;
    Homepage* home;
    userProfile* user_Profile;

private:
    Ui::XFitGymClass ui;
};
