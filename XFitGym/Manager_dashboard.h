#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_manager_dashboard.h"
class Manager_dashboard : public QWidget
{
    Q_OBJECT

public:
    Manager_dashboard(QWidget* parent = nullptr);
    ~Manager_dashboard();
    Ui::Manager_DashboardClass ui;

};

