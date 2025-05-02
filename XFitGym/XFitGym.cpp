#include "XFitGym.h"
using namespace std;
XFitGym::XFitGym(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    log = new Login(this);
    dash = new Dashboard(this);
    Cgauge = new Gauge(this);
    Pgauge = new Gauge(this);
    home = new Homepage(this);

    // padel gauge level
    int Pvalue = 0;
    QString Pval = QString::number(Pvalue);
    dash->ui.PCounter->setText( Pval);
    Pgauge->setValue(Pvalue);

    /*  Attendance Marking
    dash->setAttendance(num, true);*/

    // class gauge level
    int Cvalue = 0;
    QString Cval = QString::number(Cvalue);
    dash->ui.CCounter->setText(Cval);
    Cgauge->setValue(Cvalue);

    ui.Main->addWidget(log);
    ui.Main->addWidget(home);
    home->ui.Pages->addWidget(dash);

    if (!dash->ui.PadelGauge->layout()) {
        dash->ui.PadelGauge->setLayout(new QVBoxLayout);
        dash->ui.ClassGauge->setLayout(new QVBoxLayout);
    }
    dash->ui.PadelGauge->layout()->addWidget(Pgauge);
    dash->ui.ClassGauge->layout()->addWidget(Cgauge);

    // just for the show password functionality 
    QIcon show = QIcon("assets/showPassword.png");
    QIcon hide = QIcon("assets/hidePassword.png");
    log->ui.Password->setMaxLength(30);
    log->ui.warning->setVisible(false);

    connect(log->ui.Login, &QPushButton::clicked, this, [=]() {
        // replace true with the conditionn

        /*if (true) {
            log->ui.warning->setVisible(true);
            QTimer::singleShot(2000, log->ui.warning, &QLabel::hide);
            return;
        }*/

        QString username = log->ui.Email->text();
        QString password = log->ui.Password->text();
        if (!log->CheckLogin(username, password)) {
            if (username.isEmpty() || password.isEmpty()) {
                log->ui.warning->setText("please fill in all the spaces");
                log->ui.warning->setVisible(true);

                QTimer::singleShot(2000, log->ui.warning, &QLabel::hide);
                return;
            }
            log->ui.warning->setText("Email or Password is incorrect");
            log->ui.warning->setVisible(true);

            QTimer::singleShot(2000, log->ui.warning, &QLabel::hide);
            return;
            // QMessageBox::warning(this, "Login gamed nik", "your name is");
        }
        
        log->ui.Email->setText("");
        log->ui.Password->setText("");
        qDebug() << "LogIn";
        log->ui.showPassword->setIcon(hide);
        log->ui.Password->setEchoMode(QLineEdit::Password);
        ui.Main->setCurrentIndex(1);
        
    });
    connect(log->ui.Exit, &QPushButton::clicked, this, QApplication::quit);
    connect(log->ui.showPassword, &QPushButton::clicked, this, [=]() {
        if (log->ui.showPassword->icon().pixmap(100,100).toImage() == hide.pixmap(100, 100).toImage())
        {
            log->ui.showPassword->setIcon(show);
            log->ui.Password->setEchoMode(QLineEdit::Normal);
        }
        else if (log->ui.showPassword->icon().pixmap(100, 100).toImage() == show.pixmap(100, 100).toImage()) {
            log->ui.showPassword->setIcon(hide);
            log->ui.Password->setEchoMode(QLineEdit::Password);
        }
        });


    // user homepage control panel
    connect(home->ui.Dashboard, &QPushButton::clicked, this, [=]() {
        home->ui.Pages->setCurrentIndex(1);

    });
    connect(home->ui.Profile, &QPushButton::clicked, this, [=]() {
        qDebug() << "Profile";
        });
    connect(home->ui.Classes, &QPushButton::clicked, this, [=]() {
        qDebug() << "Classes";
    });
    connect(home->ui.Courts, &QPushButton::clicked, this, [=]() {
        qDebug() << "Padel Courts";
        });
    connect(home->ui.Notifications, &QPushButton::clicked, this, [=]() {
        qDebug() << "Notifications";
        });
    connect(home->ui.Logout, &QPushButton::clicked, this, [=]() {
        home->ui.Pages->setCurrentIndex(0);
        ui.Main->setCurrentIndex(0);

        });


}

XFitGym::~XFitGym()
{}
