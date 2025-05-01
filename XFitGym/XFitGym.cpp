#include "XFitGym.h"

XFitGym::XFitGym(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    log = new Login(this);
    ui.Main->addWidget(log);
    connect(log->ui.Login, &QPushButton::clicked, this, [=]() {
        log->ui.Email->setText("");
        log->ui.Password->setText("");
        qDebug() << "LogIn";
        });
    connect(log->ui.Exit, &QPushButton::clicked, this, QApplication::quit);

}

XFitGym::~XFitGym()
{}
