#include "Manager.h"

Manager::Manager()
{

}

Manager::Manager(QString id, QString email, QString name, QString DateOFBirth, QString role)
    : Staff(id, email, name, DateOFBirth, role)
{

}

void Manager::AddMember(Customer customer)
{
    QString id = customer.getId();
    Login::membersData.insert({ id, customer });
}
void Manager::RemoveMember(QString userID)
{
    for (auto it = Login::membersData.begin(); it != Login::membersData.end(); it++) {
        if (userID == it->first) {
            Login::membersData.erase(it);
            break;
        }
    }
}

void Manager::RenewSubscription(QString userID, int Startdate, QString plan)
{
}

void Manager::AddCoach(Coach coach)
{
    QString id = coach.getId();
    Staff::staffData.insert({ id, coach });
}
void Manager::RemoveStaff(QString staffId) 
{
    for (auto it = Staff::staffData.begin(); it != Staff::staffData.end(); it++) {
        if (staffId == it->first) {
            Staff::staffData.erase(it);
            break;
        }
    }
    for (auto it = Coach::coachData.begin(); it != Coach::coachData.end(); it++) {
        if (staffId == it->first) {
            Coach::coachData.erase(it);
            break;
        }
    }

}
void Manager::AddReceptionist(Receptionist receptionist)
{
    QString id = receptionist.getId();
    Staff::staffData.insert({ id, receptionist });
}

int Manager::discountHalfCounter = 0;
int Manager::discountQuarterCounter = 0;
int Manager::discountTenthCounter = 0;
double Manager::totalSubFees = 0.0;

