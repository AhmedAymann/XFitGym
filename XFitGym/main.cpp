#include "XFitGym.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XFitGym w;
    w.load();
    w.show();
    return a.exec();
    //khalx
}
