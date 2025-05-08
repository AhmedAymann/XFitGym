#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_manager_members.h"
class Manager_members : public QWidget
{
    Q_OBJECT

public:
    Manager_members(QWidget* parent = nullptr);
    ~Manager_members();
    Ui::Manager_membersClass ui;
};

