#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_Receptionist_homepage.h"
class Receptionist_homepage : public QWidget
{
    Q_OBJECT

public:
    Receptionist_homepage(QWidget* parent = nullptr);
    ~Receptionist_homepage();
    Ui::Receptionist_homepageClass ui;
};
