#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_Receptionist_classes.h"
class Receptionist_classes : public QWidget
{
    Q_OBJECT

public:
    Receptionist_classes(QWidget* parent = nullptr);
    ~Receptionist_classes();
    Ui::Receptionist_classesClass ui;
};
