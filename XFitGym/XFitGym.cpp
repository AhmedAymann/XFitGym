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


    // just for the show password functionality 
    QIcon show = QIcon("assets/showPassword.png");
    QIcon hide = QIcon("assets/hidePassword.png");
    log->ui.Password->setMaxLength(30);
    log->ui.warning->setVisible(false);
    
    connect(log->ui.Login, &QPushButton::clicked, this, [=]() {
        QString username = log->ui.Email->text();
        QString id = log->ui.Password->text();
        if (!log->CheckLogin(username, id)) {
            if (username.isEmpty() || id.isEmpty()) {
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
        user_Profile->ui.ID->setText(Login::membersData[id.toInt()].id);
        user_Profile->ui.Name->setText(Login::membersData[id.toInt()].name);
        user_Profile->ui.DOB->setText(Login::membersData[id.toInt()].DateOFBirth);
        user_Profile->ui.Plan->setText(Login::membersData[id.toInt()].sub.name);
        
        
        qDebug() << "LogIn";
        log->ui.showPassword->setIcon(hide);
        log->ui.Password->setEchoMode(QLineEdit::Password);
        ui.Main->setCurrentIndex(1);
        
    });
    connect(log->ui.Exit, &QPushButton::clicked, this, [=]()
    {
            save();
        QApplication::quit();
    });//
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

    int Pvalue = 100;
    QString Pval = QString::number(Pvalue);
    dash->ui.PCounter->setText(Pval);
    Pgauge->setValue(Pvalue);

    // class gauge level
    int Cvalue = 10;
    QString Cval = QString::number(Cvalue);
    dash->ui.CCounter->setText(Cval);
    Cgauge->setValue(Cvalue);

    // padel gauge level

    if (!dash->ui.PadelGauge->layout()) {
        dash->ui.PadelGauge->setLayout(new QVBoxLayout);
        dash->ui.ClassGauge->setLayout(new QVBoxLayout);
    }
    dash->ui.PadelGauge->layout()->addWidget(Pgauge);
    dash->ui.ClassGauge->layout()->addWidget(Cgauge);


    // user homepage control panel
    connect(home->ui.Dashboard, &QPushButton::clicked, this, [=]() {
        /*  Attendance Marking
        dash->setAttendance(num, true);*/
       
        //dynamically generating the past workouts

        QWidget* pastWorkouts = new QWidget;
        pastWorkouts->setStyleSheet("background-color: #1e1e1e; color: white;");

        QVBoxLayout* layout = new QVBoxLayout(pastWorkouts);
        layout->setAlignment(Qt::AlignTop);
        layout->setContentsMargins(10, 10, 10, 10);
        layout->setSpacing(10);

        for (int i = 0; i < 20; i++) {
            QWidget* workouts = new QWidget(pastWorkouts);
            workouts->setObjectName("workout");
            workouts->setFixedHeight(70);
            workouts->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            workouts->setStyleSheet(
                "#workout {"
                "background-color: #4A4A4A;"
                "border: 2px solid #8B50FF;"
                "border-radius: 14px;"
                "}"
            );

            QLabel* className = new QLabel("Zumba Class", workouts);
            className->setStyleSheet("color: white;font-family: 'Futura'; font-weight: bold; font-size: 14pt; background: transparent;");
            className->adjustSize();
            className->move(15, 10);

            QLabel* coach = new QLabel("Coach Ahmed", workouts);
            coach->setStyleSheet("color: white;font-family: 'DM Serif Display'; font-size: 10pt; background: transparent;");
            coach->adjustSize();
            coach->move(15, className->y() + className->height() + 5);  // just below class name

            QLabel* date = new QLabel("2025-05-04", workouts);
            date->setStyleSheet("color: #CCCCCC;font-family: 'DM Serif Display'; font-size: 10pt; background: transparent;");
            date->adjustSize();

            QTimer::singleShot(0, [=]() {
                int w = workouts->width();
                int h = workouts->height();
                date->move((w - date->width()) / 2 + 35, coach->y());
                });

            layout->addWidget(workouts);
        }

        pastWorkouts->setLayout(layout);
        dash->ui.scrollArea->setWidget(pastWorkouts);
        dash->ui.scrollArea->setWidgetResizable(true);




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

        //dynamically generating the notifications
        for (int i = 0; i < 20; i++) {
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
    

        //dynamically generating the Classes

        QWidget* Classes = new QWidget;
        Classes->setStyleSheet("background-color: #1e1e1e; color: white;");

        QVBoxLayout* layoutClass = new QVBoxLayout(Classes);
        layoutClass->setAlignment(Qt::AlignTop);
        layoutClass->setContentsMargins(10, 10, 10, 10);
        layoutClass->setSpacing(10);

        for (int i = 0; i < 20; i++) {
            QWidget* activeClass = new QWidget(Classes);
            activeClass->setObjectName("workout");
            activeClass->setFixedHeight(70);
            activeClass->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            activeClass->setStyleSheet(
                "#workout {"
                "background-color: #4A4A4A;"
                "border: 2px solid #8B50FF;"
                "border-radius: 14px;"
                "}"
            );

            QLabel* className = new QLabel("Zumba Class", activeClass);
            className->setStyleSheet("color: white;font-family: 'Futura'; font-weight: bold; font-size: 14pt; background: transparent;");
            className->adjustSize();
            className->move(15, 10);

            QLabel* coach = new QLabel("Coach Ahmed", activeClass);
            coach->setStyleSheet("color: white;font-family: 'DM Serif Display'; font-size: 10pt; background: transparent;");
            coach->adjustSize();
            coach->move(15, className->y() + className->height() + 5);  // just below class name

            QLabel* date = new QLabel("2025-05-04", activeClass);
            date->setStyleSheet("color: #CCCCCC;font-family: 'DM Serif Display'; font-size: 10pt; background: transparent;");
            date->adjustSize();

            QPushButton* cancelClass = new QPushButton("Cancel", activeClass);
            cancelClass->setStyleSheet(
                "QPushButton {"
                "  background-color: #2c2c2c;"
                "  color: white;"
                "  font-family: 'Futura';"
                "  font-size: 11pt;"
                "  padding: 6px 16px;"
                "  border: 2px solid #2c2c2c;"
                "  border-radius: 6px;"
                "}"
                "QPushButton:hover {"
                "  background-color: #FF0000;"
                "  border: 2px solid #FF0000;"
                "  color: white;"
                "}"
                "QPushButton:pressed {"
                "  background-color: #c0392b;"
                "}"
            );
            cancelClass->adjustSize();
            QTimer::singleShot(0, [=]() {
                int w = activeClass->width();
                cancelClass->move(w - cancelClass->width() - 15, 20);
                   });

            QTimer::singleShot(0, [=]() {
                int w = activeClass->width();
                int h = activeClass->height();
                date->move((w - date->width()) / 2 + 35, coach->y());
                });

            layoutClass->addWidget(activeClass);

            QObject::connect(cancelClass, &QPushButton::clicked, [=]() {
                activeClass->deleteLater();
                });
        }

        Classes->setLayout(layoutClass);
        user_Profile->ui.scrollAreaClass->setWidget(Classes);
        user_Profile->ui.scrollAreaClass->setWidgetResizable(true);


        //dynamically generating the Courts

        QWidget* Courts = new QWidget;
        Courts->setStyleSheet("background-color: #1e1e1e; color: white;");

        QVBoxLayout* layoutCourt = new QVBoxLayout(Courts);
        layoutCourt->setAlignment(Qt::AlignTop);
        layoutCourt->setContentsMargins(10, 10, 10, 10);
        layoutCourt->setSpacing(10);

        for (int i = 0; i < 20; i++) {
            QWidget* activeCourt = new QWidget(Courts);
            activeCourt->setObjectName("workout");
            activeCourt->setFixedHeight(70);
            activeCourt->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            activeCourt->setStyleSheet(
                "#workout {"
                "background-color: #4A4A4A;"
                "border: 2px solid #8B50FF;"
                "border-radius: 14px;"
                "}"
            );

            QLabel* className = new QLabel("Zumba Class", activeCourt);
            className->setStyleSheet("color: white;font-family: 'Futura'; font-weight: bold; font-size: 14pt; background: transparent;");
            className->adjustSize();
            className->move(15, 10);

            QLabel* coach = new QLabel("Coach Ahmed", activeCourt);
            coach->setStyleSheet("color: white;font-family: 'DM Serif Display'; font-size: 10pt; background: transparent;");
            coach->adjustSize();
            coach->move(15, className->y() + className->height() + 5);  // just below class name

            QLabel* date = new QLabel("2025-05-04", activeCourt);
            date->setStyleSheet("color: #CCCCCC;font-family: 'DM Serif Display'; font-size: 10pt; background: transparent;");
            date->adjustSize();


            QPushButton* cancelCourt = new QPushButton("Cancel", activeCourt);
            cancelCourt->setStyleSheet(
                "QPushButton {"
                "  background-color: #2c2c2c;"
                "  color: white;"
                "  font-family: 'Futura';"
                "  font-size: 11pt;"
                "  padding: 6px 16px;"
                "  border: 2px solid #2c2c2c;"
                "  border-radius: 6px;"
                "}"
                "QPushButton:hover {"
                "  background-color: #FF0000;"
                "  border: 2px solid #FF0000;"
                "  color: white;"
                "}"
                "QPushButton:pressed {"
                "  background-color: #c0392b;"
                "}"
            );
            cancelCourt->adjustSize();
            QTimer::singleShot(0, [=]() {
                int w = activeCourt->width();

                cancelCourt->move(w - cancelCourt->width() - 15, 20);
                });


            QTimer::singleShot(0, [=]() {
                int w = activeCourt->width();
                int h = activeCourt->height();
                date->move((w - date->width()) / 2 + 35, coach->y());
                });

            layoutCourt->addWidget(activeCourt);

            QObject::connect(cancelCourt, &QPushButton::clicked, [=]() {
                activeCourt->deleteLater();
                });

        }

        Courts->setLayout(layoutCourt);
        user_Profile->ui.scrollAreaCourt->setWidget(Courts);
        user_Profile->ui.scrollAreaCourt->setWidgetResizable(true);




        home->ui.Pages->setCurrentIndex(3);
        qDebug() << "Profile";
        });
    connect(home->ui.Logout, &QPushButton::clicked, this, [=]() {
        log->ui.Email->setText("");
        log->ui.Password->setText("");
        setScrolltoTop();
        home->ui.Pages->setCurrentIndex(0);
        ui.Main->setCurrentIndex(0);
       

    });
    
    connect(user_Profile->ui.viewPlans, &QPushButton::clicked, this, [=]() {
        home->ui.Pages->setCurrentIndex(1);
    });
    connect(user_Profile->ui.Cancel, &QPushButton::clicked, this, [=]() {
        user_Profile->ui.Plan->setText("No Subscription");
        Login::membersData[log->ui.Password->text().toInt()].sub.name.clear();
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
        Customer c;
        c.GiveFeedback(feed);
        feedback->ui.message->setText("Feedback submitted!");
        feedback->ui.message->setStyleSheet("color: green;");
        feedback->ui.message->setVisible(true);
        QTimer::singleShot(1250, feedback->ui.message, &QLabel::hide);

        
        feedback->ui.Feed->clear();
        });

}

XFitGym::~XFitGym()
{}

void XFitGym::setScrolltoTop()
{
    user_Profile->ui.scrollArea->verticalScrollBar()->setValue(0);
    notifications->ui.scrollArea->verticalScrollBar()->setValue(0);
    dash->ui.scrollArea->verticalScrollBar()->setValue(0);
}

void XFitGym::save()
{
    feedback->saveFeedBack();
}

void XFitGym::load()
{
    feedback->loadFeedBack();
}
