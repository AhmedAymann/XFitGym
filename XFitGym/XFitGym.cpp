#include "XFitGym.h"

XFitGym::XFitGym(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    log = new Login(this);
    ui.Main->addWidget(log);
}

XFitGym::~XFitGym()
{}
