#include "Coach.h"

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
}