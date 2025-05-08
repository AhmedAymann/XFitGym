#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_manager_homepage.h"
class Manager_homepage : public QWidget
{
	Q_OBJECT

public:
    Manager_homepage(QWidget* parent = nullptr);
    ~Manager_homepage();
    Ui::ManagerClass ui;
};

