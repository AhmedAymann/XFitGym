#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_Staff_profile.h"
class Staff_profile : public QWidget
{
    Q_OBJECT

public:
    Staff_profile(QWidget* parent = nullptr);
    ~Staff_profile();
    Ui::Staff_profileClass ui;
};