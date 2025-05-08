#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_manager_staff.h"
class Manager_staff : public QWidget
{
    Q_OBJECT

public:
    Manager_staff(QWidget* parent = nullptr);
    ~Manager_staff();
    Ui::Manager_StaffClass ui;
};

