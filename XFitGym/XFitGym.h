#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_XFitGym.h"

class XFitGym : public QMainWindow
{
    Q_OBJECT

public:
    XFitGym(QWidget *parent = nullptr);
    ~XFitGym();

private:
    Ui::XFitGymClass ui;
};
