#include "Login.h"
#include<qmessagebox>
#include<iostream>
#include <QFile>
#include <QTextStream>
#include"CustomerLoader.h"
#include <Staff.h>



Login::Login(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);

}
Login::~Login()
{}

bool Login::isMember;
bool Login::isStaff;
bool Login::isCoach;
bool Login::isReceptionist;

map<QString, Customer> Login::membersData= CustomerLoader::LoadCustomersFromFile("CustomerData.txt");
void Login::saveData()
{
    QFile file("CustomerData.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << file.errorString();
        return;
    } 

    QTextStream out(&file);

    for (const auto& pair : Login::membersData) {

        const QString& id = pair.first;
        const Customer& c = pair.second;

        if (c.email.isEmpty()) continue;
        QStringList baseFields;
        baseFields << id << c.email << c.name << c.DateOFBirth;

        // Subscription
        if (c.sub.type != "NoSubscription") {
            baseFields << c.sub.type << c.sub.startDate << c.sub.endDate << QString::number(c.sub.priceAfterDiscount);
        }
        else {
            baseFields << "NoSubscription";
        }

        QString basePart = baseFields.join(',');

        // Court Bookings
        QString courtPart;
        if (c.bookedCourt.empty()) {
            courtPart = "NoCourtBookings";
        }
        else {
            QStringList courtEntries;
            for (const auto& booking : c.bookedCourt) {
                QString dateStr = booking.first.toString("yyyy-MM-dd");
                courtEntries << dateStr + "," + booking.second;
            }
            courtPart = courtEntries.join(';');
        }

        // Training Sessions
        QString trainingPart;
        if (c.bookedsessions.empty()) {
            trainingPart = "NoTrainingSessions";
        }
        else {
            // Copy the queue to safely iterate
            std::queue<TrainingSession> tempQueue = c.bookedsessions;
            QStringList trainingEntries;

            while (!tempQueue.empty()) {
                const TrainingSession& session = tempQueue.front();
                QString dateStr = session.date.toString("yyyy-MM-dd");
                trainingEntries << session.name + "," + session.coachname + "," + dateStr + "," + session.time + "," + QString::number(session.id);
                tempQueue.pop();
            }

            trainingPart = trainingEntries.join(';');
        }
        //
        // Final line
        QString fullLine = basePart + "|" + courtPart + "|" + trainingPart;
        out << fullLine << "\n";
    }

    file.close();
}
bool Login::CheckLogin(QString& username, QString& id) {
    auto memberIt = membersData.find(id);
    if (memberIt != membersData.end() && memberIt->second.email == username) {
        isMember = true;
        return true;
    }
    
    auto staffIt = Staff::staffData.find(id);
    if (staffIt != Staff::staffData.end() && staffIt->second.email == username) {
        isStaff = true;
        if (staffIt->second.role.toLower() == "receptionist") {
            isReceptionist = true;
        }
        else if (staffIt->second.role.toLower() == "coach") {
            isCoach = true;
        }
        return true;
    }
    
    return false;
}
