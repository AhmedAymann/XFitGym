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
void Login::loaddata()
{

    QFile file("CustomerData.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file:" << file.errorString();

    }
    QTextStream in(&file);
    while (!in.atEnd())
    {

        QString line = in.readLine();
        QStringList parts = line.split(",");
        Customer c(parts[0], parts[1], parts[2], parts[3]);
        c.sub.type = parts[4];
        membersData[parts[0].toInt()] = c;

    }

    file.close();

}
//asdac
void Login::savedata()
{

    QFile file("CustomerData.txt"); 
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "Failed to clear file:" << file.errorString();

    }
    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        qDebug() << "Cannot open file:" << file.errorString();

    }

    QTextStream out(&file);

    for (auto& a : membersData)
    {
        out << a.first << ',' << a.second.email << ',' << a.second.name << ',' << a.second.DateOFBirth << ',' << a.second.sub.type << "\n";
    }

    file.close();

}


bool Login::CheckLogin(QString& username, QString& id)
{

    if (membersData[id.toInt()].email == username)
        return true;

    return false;
}