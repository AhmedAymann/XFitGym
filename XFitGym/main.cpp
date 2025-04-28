#include "XFitGym.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XFitGym w;
    w.show();
    return a.exec();
}
