#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_Coach_homepage.h"
#include "ui_Coach_classes.h"
class Coach_homepage : public QWidget
{
    Q_OBJECT

public:
    Coach_homepage(QWidget* parent = nullptr);
    ~Coach_homepage();
    Ui::Coach_homepageClass ui;
};

class Coach_classes : public QWidget
{
    Q_OBJECT

public:
    Coach_classes(QWidget* parent = nullptr);
    ~Coach_classes();
    Ui::Coach_classesClass ui;
};