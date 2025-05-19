#include "Receptionist.h"
#include <Classes.h>
#include <Padel.h>


Receptionist::Receptionist()
{}
Receptionist::Receptionist(QString id, QString email, QString name, QString DateOFBirth, QString role)
    : Staff(id, email, name, DateOFBirth, role)
{

}

void Receptionist::AddMember(Customer customer)
{
    QString id = customer.getId();
    Login::membersData.insert({ id, customer });
}
void Receptionist::RemoveMember(QString userID)
{
    for (auto it = Login::membersData.begin(); it != Login::membersData.end(); it++) {
        if (userID == it->first) {
            Login::membersData.erase(it);
            break;
        }
    }
}
void Receptionist::RenewSubscription(QDate& end, QString newType, QString& oldType, QDate start)
{
    if (newType.toLower() == "monthly") {
    end = end.addMonths(1);
    Subscription::monthlyCounter++;
}
    else if (newType.toLower() == "6-months") {
        end = end.addMonths(6);
        Subscription::sixmonthlyCounter++;
    }
    else if (newType.toLower() == "yearly") {
        end = end.addYears(1);
        Subscription::yearlyCounter++;
    }
    else if (newType.toLower() == "yearly vip") {
        end = end.addYears(1);
        Subscription::yearlyVIPCounter++;
    }
    oldType = newType;
}
void Receptionist::CreateClass(int ID, TrainingSession session)
{
    Classes::tempallsessions[ID] = session;
    Classes::allsessions[ID] = session;
}
void Receptionist::AddNews(QString newsText, QString photo)
{
    Padel::news.push({ newsText,photo });
}
