#include "Padel.h"
#include <QFile>
#include <QTextStream>
Padel::Padel(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}
Padel::~Padel()
{}
stack<pair<QString, QString>> Padel::news;
void Padel::loadcompetitors()
{
    QFile file("tournament.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file:" << file.errorString();

    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        competitors.push_back({ parts[0].toInt(), parts[1]});
        qDebug() << line;

    }
    sort(competitors.rbegin(), competitors.rend());
    file.close();
}
void Padel::savecompetitors()
{
    QFile file("tournament.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "Failed to clear file:" << file.errorString();

    }
    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        qDebug() << "Cannot open file:" << file.errorString();

    }

    QTextStream out(&file);
    for(int i=0;i<competitors.size();i++)
    {
        out << competitors[i].first<<"," << competitors[i].second<<'\n';
    }

    file.close();
}
void Padel::loadnews()
{
    QFile file("News.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file:" << file.errorString();

    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        news.push({parts[0],parts[1]});
        qDebug() << line;

    }
    file.close();
}

void Padel::savenews()
{
    QFile file("News.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "Failed to clear file:" << file.errorString();

    }
    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        qDebug() << "Cannot open file:" << file.errorString();

    }

    QTextStream out(&file);
    stack<pair<QString,QString>>tosave;
    for (int i = 0; i < 2; i++) {
        tosave.push({ news.top().first,news.top().second });
        news.pop();
        if (news.empty())
        {
            break;
        }
    }
    while (!tosave.empty())
    {
        out << tosave.top().first << "," << tosave.top().second << '\n';
        tosave.pop();
    }

    file.close();
}

bool Padel::deadline;