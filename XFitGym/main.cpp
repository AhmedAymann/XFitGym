#include "XFitGym.h"
#include "Subscription.h"
#include "Notifications.h"
#include "ProgramClock.h"
#include "Login.h"
#include "CustomerLoader.h"
#include <QCoreApplication>
#include <QTextStream>
#include <QtWidgets/QApplication>
#include <QTimer>
#include <QVector>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    XFitGym w;
    w.load();
    w.show();
    return a.exec();
}