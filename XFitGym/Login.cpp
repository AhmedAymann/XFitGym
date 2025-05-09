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

void Login::saveData()
{
    QFile file("CustomerData.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "Failed to clear file:" << file.errorString();
        return;
    }

    QTextStream out(&file);

    // Iterate through each entry in the map using an iterator
    for (auto it = Login::membersData.begin(); it != Login::membersData.end(); ++it) {
        const int userID = it->first;          // Get the user ID
        const Customer& member = it->second;   // Get the member's data

        // Start constructing the line
        QString line = QString::number(userID) + ",";  // User ID
        line += member.email + ",";                    // Email
        line += member.name + ",";                     // Name
        line += member.DateOFBirth + ",";              // Date of Birth (QString already formatted)

        // Subscription Type
        line += member.sub.type + ",";  // Subscription type (e.g., "yearly", "monthly", etc.)

        // If the subscription is not "NoSubscription", include the start and end dates
        if (member.sub.type != "NoSubscription") {
            line += member.sub.startDate + ",";  // Subscription start date
            line += member.sub.endDate + ",";    // Subscription end date
        }
        else {
            // For NoSubscription, we leave the dates empty
            line += ",,";
        }

        // Add the price after discount
        line += QString::number(member.sub.priceAfterDiscount) + ",";

        // Write the constructed line to the file
        out << line << "\n";
    }

    file.close();
}


bool Login::CheckLogin(QString& username, QString& id)
{

    if (membersData[id.toInt()].email == username)
        return true;

    return false;
}