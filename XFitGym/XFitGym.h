#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_XFitGym.h"
#include "Login.h"

class XFitGym : public QMainWindow
{
    Q_OBJECT

public:
    XFitGym(QWidget *parent = nullptr);
    ~XFitGym();
    Login* log;

private:
    Ui::XFitGymClass ui;
};
