#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_Classes.h"
#include"TrainingSession.h"
#include "Coach.h"
#include<map>

class Classes : public QWidget
{
    Q_OBJECT

public:
    Classes(QWidget* parent = nullptr);
    ~Classes();
    Ui::ClassesClass ui;

    static map<int, TrainingSession> allsessions;
    static map<int, TrainingSession> tempallsessions;

    void savesession();
    void loadsession();


};
