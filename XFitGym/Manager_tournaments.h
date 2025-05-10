#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_manager_tournaments.h"
class Manager_tournaments : public QWidget
{
    Q_OBJECT

public:
    Manager_tournaments(QWidget* parent = nullptr);
    ~Manager_tournaments();
    Ui::Manager_tournamentsClass ui;
};