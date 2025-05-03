#include "XFitGym.h"
using namespace std;

// Pages Guide:
// 
// -- HomePage --
// 0 -> Welcome Page
// 1 -> View Plans
// 2 -> Dashboard
// 3 -> User Profile
// 4 -> Notifications
// 5 -> Feedback
// 
// 
//

XFitGym::XFitGym(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    log = new Login(this);
    dash = new Dashboard(this);
    Cgauge = new Gauge(this);
    Pgauge = new Gauge(this);
    home = new Homepage(this);
    user_Profile = new userProfile(this);
    notifications = new Notifications(this);
    feedback = new Feedback(this);

    ui.Main->addWidget(log);
    ui.Main->addWidget(home);
    home->ui.Pages->addWidget(dash);
    home->ui.Pages->addWidget(user_Profile);
    home->ui.Pages->addWidget(notifications);
    home->ui.Pages->addWidget(feedback);


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
        /*  Attendance Marking
        dash->setAttendance(num, true);*/


        // padel gauge level
        int Pvalue = 0;
        QString Pval = QString::number(Pvalue);
        dash->ui.PCounter->setText(Pval);
        Pgauge->setValue(Pvalue);

        // class gauge level
        int Cvalue = 0;
        QString Cval = QString::number(Cvalue);
        dash->ui.CCounter->setText(Cval);
        Cgauge->setValue(Cvalue);

        setScrolltoTop();
        home->ui.Pages->setCurrentIndex(2);
    });
    connect(home->ui.Notifications, &QPushButton::clicked, this, [=]() {
        setScrolltoTop();

        // *************************************************************************

        //replace true with the condition notificationsVector.isEmpty()

        if (true) {
            notifications->ui.emptyMessage->setVisible(true);
            home->ui.Pages->setCurrentIndex(4);
            return;
        }
        // *************************************************************************

        QWidget* notificationWidget = new QWidget;
        notificationWidget->setStyleSheet("background-color: #1e1e1e; color: white;");
        notificationWidget->setMinimumWidth(notifications->ui.scrollArea->width() - 20);

        QVBoxLayout* layout = new QVBoxLayout(notificationWidget);
        layout->setAlignment(Qt::AlignTop);

        for (int i = 0; i < 20; ++i) {
            QWidget* notification = new QWidget(notificationWidget);
            notification->setObjectName("notification");
            notification->setStyleSheet("#notification {"
                "background-color: #4A4A4A;"
                "border: 2px solid #8B50FF;"
                "border-radius: 14px;"
                "}");
            QLabel* label = new QLabel(notification);
            label->setText(QString("test."));
            label->setWordWrap(true);
            label->setStyleSheet("color: white; font: 20pt 'DM Serif Display'; background-color:transparent;");
            label->setFixedWidth(notificationWidget->width() - 40);
            QVBoxLayout* itemLayout = new QVBoxLayout(notification);
            itemLayout->setAlignment(Qt::AlignCenter);
            itemLayout->addWidget(label);
            label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
            layout->addWidget(notification);
        }
        notificationWidget->setLayout(layout);
        notifications->ui.scrollArea->setWidget(notificationWidget);
        notifications->ui.scrollArea->setWidgetResizable(true);
        home->ui.Pages->setCurrentIndex(4);
        });
    connect(home->ui.Classes, &QPushButton::clicked, this, [=]() {
        setScrolltoTop();
        qDebug() << "Classes";
        });
    connect(home->ui.Courts, &QPushButton::clicked, this, [=]() {
        setScrolltoTop();
        qDebug() << "Padel Courts";
        });
    connect(home->ui.Feedback, &QPushButton::clicked, this, [=]() {
        setScrolltoTop();
        home->ui.Pages->setCurrentIndex(5);
        qDebug() << "Feedback";
        });
    connect(home->ui.Profile, &QPushButton::clicked, this, [=]() {
        setScrolltoTop();
        home->ui.Pages->setCurrentIndex(3);
        qDebug() << "Profile";
        });
    connect(home->ui.Logout, &QPushButton::clicked, this, [=]() {
        setScrolltoTop();
        home->ui.Pages->setCurrentIndex(0);
        ui.Main->setCurrentIndex(0);
    });
    
    connect(user_Profile->ui.viewPlans, &QPushButton::clicked, this, [=]() {
        home->ui.Pages->setCurrentIndex(1);
    });
    connect(home->ui.BacktoProf, &QPushButton::clicked, this, [=]() {
        home->ui.Pages->setCurrentIndex(3);
    });
    connect(feedback->ui.submitFeed, &QPushButton::clicked, this, [=]() {
        QString feed = feedback->ui.Feed->toPlainText();
        if (feedback->ui.Feed->toPlainText().isEmpty())
        {
            feedback->ui.message->setText("Feedback is empty");
            feedback->ui.message->setStyleSheet("color: red;");
            feedback->ui.message->setVisible(true);
            QTimer::singleShot(1250, feedback->ui.message, &QLabel::hide);
            return;
        }
        feedback->ui.message->setText("Feedback submitted!");
        feedback->ui.message->setStyleSheet("color: green;");
        feedback->ui.message->setVisible(true);
        QTimer::singleShot(1250, feedback->ui.message, &QLabel::hide);

        qDebug() << feed;
        feedback->ui.Feed->clear();
        });


}

XFitGym::~XFitGym()
{}

void XFitGym::setScrolltoTop()
{
    user_Profile->ui.scrollArea->verticalScrollBar()->setValue(0);
    notifications->ui.scrollArea->verticalScrollBar()->setValue(0);
}
