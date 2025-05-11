#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_Receptionist_members.h"
class Receptionist_members : public QWidget
{
    Q_OBJECT

public:
    Receptionist_members(QWidget* parent = nullptr);
    ~Receptionist_members();
    Ui::Receptionist_membersClass ui;
};
