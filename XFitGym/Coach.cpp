#include "Coach.h"
#include "Login.h"

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
    for (auto& a : Login::membersData)
    {
        int size=a.second.bookedsessions.size();
        for (int i = 0; i < size; i++)
        {
            TrainingSession tr = a.second.bookedsessions.front();
            if (tr.id == id)
            {
                a.second.bookedsessions.pop();
            }
            else
            {
                a.second.bookedsessions.push(tr);
                a.second.bookedsessions.pop();
            }
        }
    }
}
