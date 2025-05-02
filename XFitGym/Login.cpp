#include "Login.h"
#include<qmessagebox>
#include<iostream>
#include <QFile>
#include <QTextStream>


Login::Login(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    
}
Login::~Login()
{}

<<<<<<< HEAD


void Login::StartLogin() {
    QString username = ui.Email->text();
    QString password = ui.Password->text();
    if (CheckLogin(username, password)) {
       // QMessageBox::warning(this, "Login gamed nik", "your name is");
    }
    else
    {
       // QMessageBox::warning(this, "Warning", "incorrect Email or Password");

    }
    ui.Email->clear();
    ui.Password->clear();
}


=======
>>>>>>> 24eb0fb27230d4653d65f056c691f24e6f140265
bool Login::CheckLogin(QString& username, QString& password)
{
    QFile file("data.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file:" << file.errorString();
        return false;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        if (parts[0] == username && parts[1] == password) {

            return true;
        }
    }

    return false;
}