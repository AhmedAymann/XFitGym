#include "User.h"
#include "Staff.h"
#include <qfile.h>
#include <QTextStream>
#include <Coach.h>
#include <Receptionist.h>

map<QString, Staff> Staff::staffData;

Staff::Staff()
{
}

Staff::Staff(QString id, QString email, QString name,QString DateOFBirth, QString role)
    : User(id, email, name, DateOFBirth)
{
    this->role = role;
}
void Staff::LoadStaffData()
{
    const QString& filename = "staff.txt";
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split(',');
        if (parts.size() < 1) continue;

        QString id = parts[0];
        QString username = parts[1];
        QString name = parts[2];
        QString dob = parts[3];
        QString role = parts[4];

        if (role.toLower() == "coach") {
            Coach c(id,username,name,dob,role);
            Coach::coachData.insert({ id,c });
        }
        else if (role.toLower() == "receptionist") {
            Receptionist r(id,username,name,dob,role,"");
            Receptionist::recepData.insert({ id, r });
        }
        Staff s(id, username,name, dob, role);
        staffData.insert({ id,s });
    }
        file.close();

}
void Staff::SaveStaffData()
{
    const QString& filename = "staff.txt";
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        return;
    }
    QTextStream out(&file);

    for (auto s : staffData) {
        if (s.second.email.isEmpty()) continue;
        out << s.first << "," << s.second.email << "," << s.second.name << "," << s.second.DateOFBirth << "," << s.second.role << '\n';
    }

    file.close();
}
