#include "Coach.h"

map<QString, Coach> Coach::coachData;

Coach::Coach(QString id, QString email, QString name, QString DateOFBirth, QString role)
    : Staff(id, email, name,DateOFBirth,role)
{  
}
Coach::Coach() 
{

}
void Coach::CancelSession(int id)
{
    for (auto it = Classes::tempallsessions.begin(); it != Classes::tempallsessions.end(); it++) {
        if (it->second.id == id) {
            Classes::tempallsessions.erase(it);
            break;
        }
    }
    for (auto it = Classes::allsessions.begin(); it != Classes::allsessions.end(); it++) {
        if (it->second.id == id) {
            Classes::allsessions.erase(it);
            break;
        }
    }
}
