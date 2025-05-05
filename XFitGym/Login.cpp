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
map<int, Customer> Login::membersData;

bool Login::CheckLogin(QString& username, QString& id)
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
        if (parts[0] == username && parts[1] == id) {
            Customer c(parts[1],parts[0],parts[2],parts[3]);
            if (parts[4].isEmpty()) {
                parts[4] = "No Subscription";
            }
            c.sub.name = parts[4];
            membersData[id.toInt()] = c;
            return true;
        }
    }
    file.close();
    return false;
}