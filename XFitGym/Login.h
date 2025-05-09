#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_login.h"
#include "qtimer.h"
#include "Customer.h"
#include"Subscription.h"
#include<map>

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget* parent = nullptr);
    ~Login();
    static map<int, Customer> membersData;
    void loaddata();
    void saveData();

    Ui::LoginClass ui;

public slots:
    bool CheckLogin(QString& username, QString& id);

};