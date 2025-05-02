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