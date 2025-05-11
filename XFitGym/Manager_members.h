#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_manager_members.h"
#include "ui_renewPage.h"
class Manager_members : public QWidget
{
    Q_OBJECT

public:
    Manager_members(QWidget* parent = nullptr);
    ~Manager_members();
    Ui::Manager_membersClass ui;
};

class renewMembers : public QMainWindow
{
    Q_OBJECT

public:
    renewMembers(QWidget* parent = nullptr);
    ~renewMembers();
    Ui::renewMembersClass ui;

};