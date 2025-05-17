#include "Classes.h"
#include <QFile>
#include "qdatetime.h"
#include <QTextStream>


Classes::Classes(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}
Classes::~Classes()
{}

map<int, TrainingSession> Classes:: allsessions;
map<int, TrainingSession> Classes:: tempallsessions;

void Classes::savesession()
{
    QFile file("sessions.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "Failed to clear file:" << file.errorString();

    }
    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        qDebug() << "Cannot open file:" << file.errorString();

    }

    QTextStream out(&file);

    for (auto a : tempallsessions) {

        QString line = QString::number(a.first) + "," +
            a.second.name + "," +
            QString::number(a.second.capacity) + "," +
            QString::number(a.second.size) + "," +
            a.second.coachname + "," +
            a.second.date.toString("yyyy-MM-dd") + "," +
            a.second.time;

        out << line << "\n";
    }
    file.close();
}

void Classes::loadsession()
{
    QFile file("sessions.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file:" << file.errorString();

    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split(',');
        int id = parts[0].toInt();
        QString name = parts[1];
        int capacity = parts[2].toInt();
        int size = parts[3].toInt();
        QString coachname = parts[4];
        QDate date = QDate::fromString(parts[5], "yyyy-MM-dd");
        QString time = parts[6];


        TrainingSession session(id, name, capacity, size, coachname, date, time);
        
        allsessions[id] = session;
    }
    tempallsessions = allsessions;
    file.close();
}
