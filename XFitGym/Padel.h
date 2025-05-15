#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_Padel.h"
#include<vector>
#include<stack>
using namespace std;

class Padel : public QWidget
{
    Q_OBJECT

public:
    static stack<pair<QString, QString>>news;
    static bool deadline;
    Padel(QWidget* parent = nullptr);
    ~Padel();
    Ui::PadelClass ui;
    QPushButton* selectedSlot = nullptr;
    QString selectedDay;
    QString selectedTime;
    vector<pair<int, QString>> competitors;

    void loadcompetitors();
    void savecompetitors();

    void loadnews();
    void savenews();

};
