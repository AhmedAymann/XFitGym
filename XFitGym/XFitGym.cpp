#include "XFitGym.h"
using namespace std;

// Pages Guide:
// 
// -- ALL PAGES --
// 0 -> Login
// 1 -> User Homepage
// 2 -> Manager Homepage
// ************************************
// -- User HomePage --                *
// 0 -> Welcome Page                  *
// 1 -> View Plans                    *
// 2 -> Dashboard                     *
// 3 -> User Profile                  *
// 4 -> Notifications                 *
// 5 -> Feedback                      *
// 6 -> Classes                       *
// 7 -> Padel                         *
// ************************************
// -- Manager HomePage --             *
// 0 -> Welcome Page                  *
// 1 -> Dashboard                     *
// 2 -> Member                        *
// 3 -> Staff                         *
// 4 -> Tournaments                   *
// 5 -> Feedback                      *
// 
// ************************************
//

void reorganizeGrid(QGridLayout* grid, QPushButton* addCard) {
    grid->removeWidget(addCard);
    QList<QWidget*> cards;
    for (int i = 0; i < grid->count(); i++) {
        QWidget* widget = grid->itemAt(i)->widget();
        if (widget && widget != addCard) {
            cards.append(widget);
        }
    }
    while (grid->count() > 0) {
        grid->takeAt(0);
    }
    for (int i = 0; i < cards.size(); ++i) {
        int row = i / 3;
        int col = i % 3;
        grid->addWidget(cards[i], row, col);
    }
    int addRow = cards.size() / 3;
    int addCol = cards.size() % 3;
    grid->addWidget(addCard, addRow, addCol);
}

XFitGym::XFitGym(QWidget* parent)
    : QMainWindow(parent)
{
    QVector<Cards*>* memberCardsList = nullptr;

    ui.setupUi(this);
    log = new Login(this);
    dash = new Dashboard(this);
    Cgauge = new Gauge(this);
    Pgauge = new Gauge(this);
    home = new Homepage(this);
    user_Profile = new userProfile(this);
    notifications = new Notifications(this);
    feedback = new Feedback(this);
    classes = new Classes(this);
    padel = new Padel(this);
    man_home = new Manager_homepage(this);
    man_dash = new Manager_dashboard(this);
    man_members = new Manager_members(this);
    man_staff = new Manager_staff(this);
    man_tournaments = new Manager_tournaments(this);
    man_feedback = new Manager_feedback(this);

    ui.Main->addWidget(log);
    ui.Main->addWidget(home);
    ui.Main->addWidget(man_home);

    home->ui.Pages->addWidget(dash);
    home->ui.Pages->addWidget(user_Profile);
    home->ui.Pages->addWidget(notifications);
    home->ui.Pages->addWidget(feedback);
    home->ui.Pages->addWidget(classes);
    home->ui.Pages->addWidget(padel);

    man_home->ui.Pages->addWidget(man_dash);
    man_home->ui.Pages->addWidget(man_members);
    man_home->ui.Pages->addWidget(man_staff);
    man_home->ui.Pages->addWidget(man_tournaments);
    man_home->ui.Pages->addWidget(man_feedback);

    // just for the show password functionality 
    QIcon show = QIcon("assets/showPassword.png");
    QIcon hide = QIcon("assets/hidePassword.png");
    log->ui.ID->setMaxLength(30);
    log->ui.warning->setVisible(false);


    connect(log->ui.Login, &QPushButton::clicked, this, [=]() {
        QString username = log->ui.Email->text();
        QString id = log->ui.ID->text();

        if (username == "manager" && id == "1") {
            ui.Main->setCurrentIndex(2);
            man_home->ui.welcome->setText("Welcome Back,Manager");

            return;
        }
        qDebug() << username << " " << id;
        if (!log->CheckLogin(username, id)) {
            if (username.isEmpty() || id.isEmpty()) {
                log->ui.warning->setText("please fill in all the spaces");
                log->ui.warning->setVisible(true);

                QTimer::singleShot(2000, log->ui.warning, &QLabel::hide);
                return;
            }
            log->ui.warning->setText("Username or ID is incorrect");
            log->ui.warning->setVisible(true);

            QTimer::singleShot(2000, log->ui.warning, &QLabel::hide);
            return;
        }
        user_Profile->ui.ID->setText(Login::membersData[id].id);
        user_Profile->ui.Name->setText(Login::membersData[id].name);
        user_Profile->ui.DOB->setText(Login::membersData[id].DateOFBirth);
        if (Login::membersData[id].sub.type.isEmpty()) {
            user_Profile->ui.ID->setText(Login::membersData[id].id);
            user_Profile->ui.Name->setText(Login::membersData[id].name);
            user_Profile->ui.DOB->setText(Login::membersData[id].DateOFBirth);
            user_Profile->ui.Plan->setText("No Subscription");

        }
        else
        {
            user_Profile->ui.Plan->setText(Login::membersData[id].sub.type);
        }
        home->ui.welcome->setText("Welcome Back, " + Login::membersData[id].name);



            qDebug() << "LogIn";
            log->ui.showPassword->setIcon(hide);
            log->ui.ID->setEchoMode(QLineEdit::Password);
            ui.Main->setCurrentIndex(1);

        });
        
        connect(log->ui.Exit, &QPushButton::clicked, this, [=]()
            {
                save();
                QApplication::quit();
            });
        connect(log->ui.showPassword, &QPushButton::clicked, this, [=]() {
            if (log->ui.showPassword->icon().pixmap(100, 100).toImage() == hide.pixmap(100, 100).toImage())
            {
                log->ui.showPassword->setIcon(show);
                log->ui.ID->setEchoMode(QLineEdit::Normal);
            }
            else if (log->ui.showPassword->icon().pixmap(100, 100).toImage() == show.pixmap(100, 100).toImage()) {
                log->ui.showPassword->setIcon(hide);
                log->ui.ID->setEchoMode(QLineEdit::Password);
            }
            });



        // padel gauge levels

        if (!dash->ui.PadelGauge->layout()) {
            dash->ui.PadelGauge->setLayout(new QVBoxLayout);
            dash->ui.ClassGauge->setLayout(new QVBoxLayout);
        }
        dash->ui.PadelGauge->layout()->addWidget(Pgauge);
        dash->ui.ClassGauge->layout()->addWidget(Cgauge);


        user_Profile->ui.messageClass->setVisible(false);
        user_Profile->ui.messageCourt->setVisible(false);
        dash->ui.message->setVisible(false);


        // user homepage control panel
        connect(home->ui.Dashboard, &QPushButton::clicked, this, [=]() {

            int Pvalue = Login::membersData[user_Profile->ui.ID->text()].bookedCourt.size();
            QString Pval = QString::number(Pvalue);
            dash->ui.PCounter->setText(Pval);
            Pgauge->setValue(Pvalue);

            // class gauge level
            int Cvalue = Login::membersData[user_Profile->ui.ID->text()].bookedsessions.size();
            QString Cval = QString::number(Cvalue);
            dash->ui.CCounter->setText(Cval);
            Cgauge->setValue(Cvalue);
            /*  Attendance Marking
            dash->setAttendance(num, true);*/
            if (true)
            {
                setScrolltoTop();
                dash->ui.message->setVisible(true);
                home->ui.Pages->setCurrentIndex(2);
                return;
            }
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

            if (Notifications::notifications.empty()) {
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



            for (auto it = Notifications::notifications.begin(); it != Notifications::notifications.end(); ++it) {
                if (QString::number(it.key()) == user_Profile->ui.ID->text()) {
                    for (const QString& msg : it.value()) {
                        QWidget* notification = new QWidget(notificationWidget);
                        notification->setObjectName("notification");
                        notification->setStyleSheet("#notification {"
                            "background-color: #4A4A4A;"
                            "border: 2px solid #8B50FF;"
                            "border-radius: 14px;"
                            "}");

                        QLabel* label = new QLabel(notification);
                        label->setText(msg);
                        label->setWordWrap(true);
                        label->setStyleSheet("color: white; font: 20pt 'DM Serif Display'; background-color:transparent;");
                        label->setFixedWidth(notificationWidget->width() - 40);

                        QVBoxLayout* itemLayout = new QVBoxLayout(notification);
                        itemLayout->setAlignment(Qt::AlignCenter);
                        itemLayout->addWidget(label);
                        label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

                        layout->addWidget(notification);
                    }
                    break;
                }
            }

            notificationWidget->setLayout(layout);
            notifications->ui.scrollArea->setWidget(notificationWidget);
            notifications->ui.scrollArea->setWidgetResizable(true);

            home->ui.Pages->setCurrentIndex(4);
            });
        connect(home->ui.Classes, &QPushButton::clicked, this, [=]() {
            setScrolltoTop();
            qDebug() << "Classes";

            QWidget* scrollWidget = new QWidget;
            scrollWidget->setObjectName("scrollWidget");

            scrollWidget->setStyleSheet("QWidget#scrollWidget{background-color: #1e1e1e;}");

            QGridLayout* grid = new QGridLayout(scrollWidget);

            int numCards = 13;
            for (int i = 0; i < numCards; i++) {
                QString className = "Biceps Class";
                QString date_time = "5/5/2025    7:00 PM";
                QString coachName = "Coach: Khalx";
                int attend = 30;
                int max = 40;

                Cards* card = new Cards(className, date_time, coachName, attend, max);
                QPushButton* waitlist = new QPushButton("Waitlist");
                QPushButton* book = new QPushButton("Book");
                //************************
                //  replace true with (attendedCounter < maxSize)
                if (i < 3)
                {
                    book->setStyleSheet("background-color:#6F3FCC ;font-family: 'Futura'; color: white;");

                    waitlist->setStyleSheet("background-color: grey;font-family: 'Futura'; color: white;");
                    waitlist->setEnabled(false);
                }
                else
                {
                    waitlist->setStyleSheet("background-color:#6F3FCC;font-family: 'Futura'; color: white;");

                    book->setStyleSheet("background-color: grey;font-family: 'Futura'; color: white;");
                    book->setEnabled(false);


                }

                card->buttonLayout->addWidget(waitlist);
                card->buttonLayout->addWidget(book);

                int row = i / 3;
                int col = i % 3;
                grid->addWidget(card, row, col);

                QObject::connect(waitlist, &QPushButton::clicked, [=]() {
                    });
                QObject::connect(book, &QPushButton::clicked, [=]() {
                    qDebug() << coachName;
                    });
            }

            scrollWidget->setLayout(grid);
            classes->ui.scrollArea->setWidget(scrollWidget);
            classes->ui.scrollArea->setWidgetResizable(true);


            home->ui.Pages->setCurrentIndex(6);
            });
        connect(home->ui.Courts, &QPushButton::clicked, this, [=]() {
            setScrolltoTop();
            qDebug() << "Padel Courts";

            QWidget courts;
            // Create the grid layout
            QGridLayout* grid = new QGridLayout;
            QStringList days = { "Sat", "Sun", "Mon", "Tue", "Wed","Thu" , "Fri" }; // Full week
            QStringList times = { "12:00", "1:00", "2:00", "3:00", "4:00", "5:00", "6:00", "7:00", "8:00" }; // Updated times from 12:00 to 8:00
            int courtCount = 7;

            // Headers for weekdays (Mon, Tue, ..., Sun)
            for (int d = 0; d < days.size(); ++d)
                grid->addWidget(new QLabel(days[d]), 0, d + 1);

            // Time slots on the left
            for (int t = 0; t < times.size(); ++t)
                grid->addWidget(new QLabel(times[t]), t + 1, 0);

            // Slots for court bookings
            for (int t = 0; t < times.size(); t++) {
                for (int c = 0; c < courtCount; c++) {
                    QPushButton* slot = new QPushButton;
                    slot->setFixedSize(60, 40);
                    slot->setStyleSheet("background-color: white; border: 1px solid gray;");

                    //replace this condition when isBooked
                    if (t < 5 && c % 2 == 0)
                    {
                        slot->setStyleSheet("background-color: red;border: 1px solid gray;");
                        slot->setEnabled(false);
                    }

                    else
                    {
                        slot->setStyleSheet("background-color: green;border: 1px solid gray;");
                    }
                    grid->addWidget(slot, t + 1, c + 1); // Adding slots to grid
                    QObject::connect(slot, &QPushButton::clicked, [=]() mutable {
                        if (padel->selectedSlot) {
                            padel->selectedSlot->setStyleSheet("background-color: green;border: 1px solid gray;");
                        }

                        padel->selectedSlot = slot;
                        padel->selectedDay = days[c];
                        padel->selectedTime = times[t];
                        slot->setStyleSheet("background-color: yellow;border: 1px solid gray;"); // Highlight as selected
                        });
                }
            }


            // Assuming the QWidget you're working with is called ui->yourWidget
            padel->ui.widget->setLayout(grid);  // Set the QGridLayout to the widget
            stack<pair<QString, QString>>newsCopy = Padel::news;
            if (newsCopy.empty()) {
                padel->ui.firstNew->setText("No news");
                padel->ui.secondNew->setText("No news");
                padel->ui.firstImage->setVisible(false);
                padel->ui.secondImage->setVisible(false);
            }
            else if (newsCopy.size() == 1) {
                padel->ui.firstNew->setText(newsCopy.top().first);
                padel->ui.firstImage->setPixmap(newsCopy.top().second);
                newsCopy.pop();

                padel->ui.secondNew->setText("No news");
                padel->ui.secondImage->setVisible(false);
            }
            else {
                padel->ui.firstNew->setText(newsCopy.top().first);
                padel->ui.firstImage->setPixmap(newsCopy.top().second);
                newsCopy.pop();

                padel->ui.secondNew->setText(newsCopy.top().first);
                padel->ui.secondImage->setPixmap(newsCopy.top().second);
                newsCopy.pop();
            }

            home->ui.Pages->setCurrentIndex(7);
            });
        connect(home->ui.Feedback, &QPushButton::clicked, this, [=]() {
            setScrolltoTop();
            home->ui.Pages->setCurrentIndex(5);
            qDebug() << "Feedback";
            });


        connect(home->ui.Profile, &QPushButton::clicked, this, [=]() {
            setScrolltoTop();
            queue<TrainingSession>bookedsession = Login::membersData[user_Profile->ui.ID->text()].bookedsessions;



            //change true with (class.empty && courts.empty) .. w e3mel condition di lw7dha w di lw7dha
            if (bookedsession.empty()) {
                user_Profile->ui.messageClass->setVisible(true);
                // user_Profile->ui.messageCourt->setVisible(true);
                home->ui.Pages->setCurrentIndex(3);
                return;
            }


            //dynamically generating the Classes

            QWidget* Classes = new QWidget;
            Classes->setStyleSheet("background-color: #1e1e1e; color: white;");

            QVBoxLayout* layoutClass = new QVBoxLayout(Classes);
            layoutClass->setAlignment(Qt::AlignTop);
            layoutClass->setContentsMargins(10, 10, 10, 10);
            layoutClass->setSpacing(10);



            while (!bookedsession.empty()) {
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

                QLabel* className = new QLabel(QString::fromStdString(bookedsession.front().name), activeClass);
                className->setStyleSheet("color: white;font-family: 'Futura'; font-weight: bold; font-size: 14pt; background: transparent;");
                className->adjustSize();
                className->move(15, 10);

                QLabel* coach = new QLabel(bookedsession.front().coachname, activeClass);
                coach->setStyleSheet("color: white;font-family: 'DM Serif Display'; font-size: 10pt; background: transparent;");
                coach->adjustSize();
                coach->move(15, className->y() + className->height() + 5);  // just below class name

                QLabel* date = new QLabel(bookedsession.front().date.toString("yyyy-MM-dd"), activeClass);
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
                bookedsession.pop();
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

                QPushButton* rescheduleCourt = new QPushButton("Reschedule", activeCourt);
                rescheduleCourt->setStyleSheet(R"(
                QPushButton {
                    background-color: #2c2c2c;
                    color: white;
                    border: 2px solid #2c2c2c;
                    border-radius: 6px;
                    font-family: 'Futura';
                   font-size: 11pt;
                   padding: 6px 16px;
                }

                QPushButton:hover {
                    background-color: #8B50FF;
                    border: 2px solid #8B50FF;
                    color: white;
                }

                QPushButton:pressed {
                    background-color: #6F3FCC;
                }
            )");


                rescheduleCourt->adjustSize();
                cancelCourt->adjustSize();
                QTimer::singleShot(0, [=]() {
                    int w = activeCourt->width();
                    rescheduleCourt->move(w - cancelCourt->width() - 30 - rescheduleCourt->width(), 20);
                    cancelCourt->move(w - cancelCourt->width() - 15, 20);
                    });


                QTimer::singleShot(0, [=]() {
                    int w = activeCourt->width();
                    int h = activeCourt->height();
                    date->move((w - date->width()) / 2 + 15, coach->y());
                    });

                layoutCourt->addWidget(activeCourt);

                QObject::connect(cancelCourt, &QPushButton::clicked, [=]() {
                    activeCourt->deleteLater();
                    });

                QObject::connect(rescheduleCourt, &QPushButton::clicked, [=]() {
                    qDebug() << "Rescheduled";
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
            log->ui.ID->setText("");
            setScrolltoTop();
            home->ui.Pages->setCurrentIndex(0);
            ui.Main->setCurrentIndex(0);


            });

        connect(man_home->ui.Dashboard, &QPushButton::clicked, this, [=]() {
            man_home->ui.Pages->setCurrentIndex(1);
            });
        connect(man_home->ui.Staff, &QPushButton::clicked, this, [=]() {
            QWidget* scrollWidget = new QWidget();
            scrollWidget->setObjectName("scrollWidget");
            scrollWidget->setStyleSheet("QWidget#scrollWidget{background-color: #1e1e1e;}");

            QGridLayout* grid = new QGridLayout(scrollWidget);
            grid->setSpacing(20);
            grid->setContentsMargins(20, 20, 20, 20);

            QPushButton* addCard = new QPushButton("+", scrollWidget);
            addCard->setFixedSize(220, 160);
            addCard->setStyleSheet(R"(
        QPushButton {
            background-color: #2e2e2e;
            border: 2px dashed #6F3FCC;
            border-radius: 15px;
            color: #6F3FCC;
            font-size: 48pt;
        }
        QPushButton:hover {
            background-color: #3a3a3a;
        }
    )");
            addCard->setCursor(Qt::PointingHandCursor);

            int numStaff = 5;
            for (int i = 0; i < numStaff; ++i) {
                QString name = "Staff Member " + QString::number(i + 1);
                QString position = i % 2 ? "Trainer" : "Receptionist";
                QString joinDate = QDate::currentDate().addDays(-i * 30).toString("dd/MM/yyyy");

                Cards* staffCard = new Cards(name, position, joinDate, scrollWidget);

                QPushButton* removeBtn = new QPushButton("Remove", staffCard);
                removeBtn->setStyleSheet(R"(
            QPushButton {
                background-color: #E53935; 
                color: white; 
                font-family: 'Futura';
                padding: 5px;
                border-radius: 5px;
                min-width: 80px;
            }
            QPushButton:hover {
                background-color: #EF5350;
            }
        )");

                staffCard->buttonLayout->addWidget(removeBtn);

                int row = i / 3;
                int col = i % 3;
                grid->addWidget(staffCard, row, col);

                connect(removeBtn, &QPushButton::clicked, this, [=]() {
                    grid->removeWidget(staffCard);

                    staffCard->deleteLater();

                    reorganizeGrid(grid, addCard);
                    });
            }

            int addRow = numStaff / 3;
            int addCol = numStaff % 3;
            grid->addWidget(addCard, addRow, addCol);

            connect(addCard, &QPushButton::clicked, this, [=]() {
                qDebug() << "Add Staff Clicked";
                });

            if (man_staff->ui.scrollArea->widget()) {
                man_staff->ui.scrollArea->widget()->deleteLater();
            }
            man_staff->ui.scrollArea->setWidget(scrollWidget);
            man_staff->ui.scrollArea->setWidgetResizable(true);

            man_home->ui.Pages->setCurrentIndex(3);
            });
        connect(man_home->ui.Feedback, &QPushButton::clicked, this, [=]() {
            setScrolltoTop();
            //replace true with the condition man_feedbackVector.isEmpty()
            stack<QString> managerfeedback = Feedback::FeedBack;
            if (managerfeedback.empty()) {
                man_feedback->ui.emptyMessage->setVisible(true);
                home->ui.Pages->setCurrentIndex(4);
                return;
            }

            QWidget* feedbackWidget = new QWidget;
            feedbackWidget->setStyleSheet("background-color: #1e1e1e; color: white;");
            feedbackWidget->setMinimumWidth(man_feedback->ui.scrollArea->width() - 20);

            QVBoxLayout* layout = new QVBoxLayout(feedbackWidget);
            layout->setAlignment(Qt::AlignTop);

            //dynamically generating the feedbacks
            while (!managerfeedback.empty()) {
                QWidget* feedback = new QWidget(feedbackWidget);
                feedback->setObjectName("feedback");
                feedback->setStyleSheet("#feedback {"
                    "background-color: #4A4A4A;"
                    "border: 2px solid #8B50FF;"
                    "border-radius: 14px;"
                    "}");
                QLabel* label = new QLabel(feedback);
                label->setText(QString(managerfeedback.top()));
                label->setWordWrap(true);
                label->setStyleSheet("color: white; font: 20pt 'DM Serif Display'; background-color:transparent;");
                label->setFixedWidth(feedbackWidget->width() - 40);
                QVBoxLayout* itemLayout = new QVBoxLayout(feedback);
                itemLayout->setAlignment(Qt::AlignCenter);
                itemLayout->addWidget(label);
                label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
                layout->addWidget(feedback);
                managerfeedback.pop();
            }

            feedbackWidget->setLayout(layout);
            man_feedback->ui.scrollArea->setWidget(feedbackWidget);
            man_feedback->ui.scrollArea->setWidgetResizable(true);

            man_home->ui.Pages->setCurrentIndex(5);

            });
        connect(man_home->ui.Tournament, &QPushButton::clicked, this, [=]() {
            man_home->ui.Pages->setCurrentIndex(4);
            });
        connect(man_home->ui.Profile, &QPushButton::clicked, this, [=]() {});
        connect(man_home->ui.Logout, &QPushButton::clicked, this, [=]() {
            log->ui.Email->setText("");
            log->ui.ID->setText("");
            setScrolltoTop();
            man_home->ui.Pages->setCurrentIndex(0);
            ui.Main->setCurrentIndex(0);
            });
        connect(man_home->ui.Members, &QPushButton::clicked, this, [=]() {
            QWidget* scrollWidget = new QWidget();
            scrollWidget->setObjectName("scrollWidget");
            scrollWidget->setStyleSheet("QWidget#scrollWidget{background-color: #1e1e1e;}");

            QGridLayout* grid = new QGridLayout(scrollWidget);
            grid->setSpacing(20);
            grid->setContentsMargins(20, 20, 20, 20);

            QPushButton* addCard = new QPushButton("+", scrollWidget);
            addCard->setFixedSize(220, 160);
            addCard->setStyleSheet(R"(
        QPushButton {
            background-color: #2e2e2e;
            border: 2px dashed #6F3FCC;
            border-radius: 15px;
            color: #6F3FCC;
            font-size: 48pt;
        }
        QPushButton:hover {
            background-color: #3a3a3a;
        }
    )");
            addCard->setCursor(Qt::PointingHandCursor);

            connect(addCard, &QPushButton::clicked, this, []() {
                qDebug() << "Add Member Clicked";
                });

            int numMembers = 7;
            for (int i = 0; i < numMembers; ++i) {
                QString name = "Ahmed Salah " + QString::number(i + 1);
                QString phone = "012345678" + QString::number(i);
                QString subscription = "Ends: " + QDate::currentDate().addDays(i * 30).toString("dd/MM/yyyy");

                Cards* card = new Cards(name, phone, subscription, scrollWidget);

                QPushButton* renewBtn = new QPushButton("Renew", card);
                QPushButton* removeBtn = new QPushButton("Remove", card);

                renewBtn->setStyleSheet(R"(
            QPushButton {
                background-color: #6F3FCC; 
                color: white; 
                font-family: 'Futura';
                padding: 5px;
                border-radius: 5px;
            }
            QPushButton:hover {
                background-color: #8F5FEC;
            }
        )");

                removeBtn->setStyleSheet(R"(
            QPushButton {
                background-color: #E53935; 
                color: white; 
                font-family: 'Futura';
                padding: 5px;
                border-radius: 5px;
            }
            QPushButton:hover {
                background-color: #EF5350;
            }
        )");

                card->buttonLayout->addWidget(renewBtn);
                card->buttonLayout->addWidget(removeBtn);

                int row = i / 3;
                int col = i % 3;
                grid->addWidget(card, row, col);

                connect(removeBtn, &QPushButton::clicked, this, [grid, card, addCard]() {
                    grid->removeWidget(card);

                    card->deleteLater();

                    reorganizeGrid(grid, addCard);
                    });

                connect(renewBtn, &QPushButton::clicked, this, [name]() {
                    qDebug() << "Renew clicked for" << name;
                    });
            }

            int addRow = numMembers / 3;
            int addCol = numMembers % 3;
            grid->addWidget(addCard, addRow, addCol);

            if (man_members->ui.scrollArea->widget()) {
                man_members->ui.scrollArea->widget()->deleteLater();
            }
            man_members->ui.scrollArea->setWidget(scrollWidget);
            man_members->ui.scrollArea->setWidgetResizable(true);
            man_home->ui.Pages->setCurrentIndex(2);
            });
        connect(user_Profile->ui.viewPlans, &QPushButton::clicked, this, [=]() {
            home->ui.Pages->setCurrentIndex(1);
            });
        connect(user_Profile->ui.Cancel, &QPushButton::clicked, this, [=]() {
            user_Profile->ui.Plan->setText("No Subscription");
            Login::membersData[log->ui.ID->text()].sub.type = "No Subscription";
            user_Profile->ui.Plan->setText("NoSubscription");
            Login::membersData[log->ui.ID->text()].sub.type = "NoSubscription";
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
        connect(padel->ui.BookCourt, &QPushButton::clicked, this, [=]() {
            if (padel->selectedSlot) {
                qDebug() << "Booked:" << padel->selectedDay << padel->selectedTime;
                padel->selectedSlot->setStyleSheet("background-color: red;border: 1px solid gray;");
                padel->selectedSlot->setEnabled(false);
                padel->selectedSlot = nullptr;
            }
            else {
                qDebug() << "No slot selected!";
            }
            });
        connect(man_tournaments->ui.submit, &QPushButton::clicked, this, [=]() {

            QString firstTeam_firstName = man_tournaments->ui.FFname->text();
            QString firstTeam_secondName = man_tournaments->ui.FSname->text();
            QString firstScore = man_tournaments->ui.Fscore->text();
            QString secondTeam_firstName = man_tournaments->ui.SFname->text();
            QString secondTeam_secondName = man_tournaments->ui.SSname->text();
            QString secondScore = man_tournaments->ui.Sscore->text();
            QString thirdTeam_firstName = man_tournaments->ui.SSname->text();
            QString thirdTeam_secondName = man_tournaments->ui.SSname->text();
            QString thirdScore = man_tournaments->ui.Tscore->text();

            bool empty = (firstTeam_firstName.isEmpty() || firstTeam_secondName.isEmpty() || firstScore.isEmpty() || secondTeam_firstName.isEmpty() || secondTeam_secondName.isEmpty()
                || secondScore.isEmpty() || thirdTeam_firstName.isEmpty() || thirdTeam_secondName.isEmpty() || thirdScore.isEmpty());

            if (empty) {
                man_tournaments->ui.message->setText("Fill all the boxes");
                man_tournaments->ui.message->setStyleSheet("color:red;");
                man_tournaments->ui.message->setVisible(true);
                QTimer::singleShot(1250, man_tournaments->ui.message, &QLabel::hide);
                return;
            }
            man_tournaments->ui.message->setText("Submitted successfully!");
            man_tournaments->ui.message->setStyleSheet("color:green;");
            man_tournaments->ui.message->setVisible(true);
            QTimer::singleShot(1250, man_tournaments->ui.message, &QLabel::hide);
            man_tournaments->ui.FFname->clear();
            man_tournaments->ui.FSname->clear();
            man_tournaments->ui.SFname->clear();
            man_tournaments->ui.SSname->clear();
            man_tournaments->ui.TFname->clear();
            man_tournaments->ui.TSname->clear();
            man_tournaments->ui.Fscore->clear();
            man_tournaments->ui.Sscore->clear();
            man_tournaments->ui.Tscore->clear();


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
    notifications->saveNotifications();
    feedback->saveFeedBack();
    log->saveData();
    padel->savenews();
}

void XFitGym::load()
{
    notifications->loadNotifications();
    feedback->loadFeedBack();
    padel->loadnews();
}

Cards::Cards(QString title, QString line1, QString line2, QWidget* parent)
    : QWidget(parent)
{
    setFixedSize(220, 160);

    QVBoxLayout* outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(0, 0, 0, 0);

    QFrame* cardFrame = new QFrame;
    cardFrame->setObjectName("cardFrame");
    cardFrame->setFixedSize(220, 160);

    cardFrame->setStyleSheet(R"(
        QFrame#cardFrame {
            background-color: #4A4A4A;
            border: 2px solid #6F3FCC;
            border-radius: 15px;
        }
    )");

    QVBoxLayout* cardLayout = new QVBoxLayout(cardFrame);
    cardLayout->setContentsMargins(10, 10, 10, 10);

    QLabel* titleLabel = new QLabel("<b>" + title + "</b>");
    QLabel* line1Label = new QLabel(line1);
    QLabel* line2Label = new QLabel(line2);

    titleLabel->setStyleSheet("font-size: 18pt; font-family: 'Futura'; color: white;");
    line1Label->setStyleSheet("font-family: 'DM Serif Display'; color: white;");
    line2Label->setStyleSheet("font-family: 'DM Serif Display'; color: white;");

    buttonLayout = new QHBoxLayout();

    cardLayout->addWidget(titleLabel);
    cardLayout->addWidget(line1Label);
    cardLayout->addWidget(line2Label);
    cardLayout->addStretch();
    cardLayout->addLayout(buttonLayout);

    outerLayout->addWidget(cardFrame);
}

Cards::Cards(QString title, QString line1, QString line2, int attendees, int max, QWidget* parent)
    : QWidget(parent)
{
    setFixedSize(220, 160);

    QVBoxLayout* outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(0, 0, 0, 0);

    QFrame* cardFrame = new QFrame;
    cardFrame->setObjectName("cardFrame");
    cardFrame->setFixedSize(220, 160);
    cardFrame->setStyleSheet(R"(
        QFrame#cardFrame {
            background-color: #4A4A4A;
            border: 2px solid #6F3FCC;
            border-radius: 15px;
        }
    )");

    QVBoxLayout* cardLayout = new QVBoxLayout(cardFrame);
    cardLayout->setContentsMargins(30, 10, 10, 10);

    QLabel* titleLabel = new QLabel("<b>" + title + "</b>");
    QLabel* line1Label = new QLabel(line1);
    QLabel* line2Label = new QLabel(line2);

    titleLabel->setStyleSheet("font-size: 18pt; font-family: 'Futura'; color: white;");
    line1Label->setStyleSheet("font-family: 'DM Serif Display'; color: white;");
    line2Label->setStyleSheet("font-family: 'DM Serif Display'; color: white;");

    QHBoxLayout* attendanceLayout = new QHBoxLayout;
    attendanceLayout->setContentsMargins(50, 0, 0, 0);

    QLabel* iconLabel = new QLabel;
    iconLabel->setPixmap(QPixmap("assets/bookedMembers.png").scaled(16, 16, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QLabel* attendanceLabel = new QLabel(QString("%1/%2").arg(attendees).arg(max));
    attendanceLabel->setStyleSheet("color: white; font-size: 12px;");

    attendanceLayout->addWidget(iconLabel);
    attendanceLayout->addWidget(attendanceLabel);
    attendanceLayout->addStretch();

    buttonLayout = new QHBoxLayout();

    cardLayout->addWidget(titleLabel);
    cardLayout->addWidget(line1Label);
    cardLayout->addWidget(line2Label);
    cardLayout->addLayout(attendanceLayout);
    cardLayout->addStretch();
    cardLayout->addLayout(buttonLayout);

    outerLayout->addWidget(cardFrame);
}