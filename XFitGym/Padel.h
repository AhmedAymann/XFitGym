#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_Padel.h"
#include<stack>
using namespace std;

class Padel : public QWidget
{
    Q_OBJECT

public:
    static stack<pair<QString, QString>>news;
    Padel(QWidget* parent = nullptr);
    ~Padel();
    Ui::PadelClass ui;
    QPushButton* selectedSlot = nullptr;
    QString selectedDay;
    QString selectedTime;

    void loadnews();
    void savenews();

};
