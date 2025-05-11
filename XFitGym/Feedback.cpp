#include "Feedback.h"
#include <QFile>
#include <QTextStream>

Feedback::Feedback(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);

}
Feedback::~Feedback()
{}
stack<QString> Feedback::FeedBack;

void Feedback::saveFeedBack()
{
    
    QFile file("feedbacks.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "Failed to clear file:" << file.errorString();
        
    }
    if (!file.open(QIODevice::Append | QIODevice::Text)) 
    {
        qDebug() << "Cannot open file:" << file.errorString();
       
    }
     
    QTextStream out(&file);
    stack<QString>tosave;
    while (!FeedBack.empty())
    {
        tosave.push(FeedBack.top());
        FeedBack.pop();
    }
    while(!tosave.empty())
    {
        out << tosave.top() << '\n';
        tosave.pop();
    }
    file.close();
    
}

void Feedback::loadFeedBack()
{
    QFile file("feedbacks.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file:" << file.errorString();
        
    }
    QTextStream in(&file);
    while (!in.atEnd()) 
    {
        QString line = in.readLine();
        FeedBack.push(line);
        qDebug() << line;
       
    }
    
    file.close();

    
}
