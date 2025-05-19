#include "XFitGym.h"
#include <CustomerLoader.h>
using namespace std;

// Pages Guide:
// ************************************
// -- ALL PAGES --                    *
// 0 -> Login                         *
// 1 -> User Homepage                 *
// 2 -> Manager Homepage              *
// 3 -> Coach Homepage                *
// 4 -> Receptionist Homepage         *
// ************************************
// -- User HomePage --                *
// 0 -> Welcome Page                  *
// 1 -> View Plans                    *
// 2 -> Dashboard                     *
// 3 -> Profile                       *
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
// 6 -> Profile                       *
// ************************************
// -- Coach HomePage --               *
// 0 -> Welcome Page                  *
// 1 -> Profile                       *
// 2 -> Classes                       *
// ************************************
// -- Receptionist HomePage --        *
// 0 -> Welcome Page                  *
// 1 -> Profile                       *
// 2 -> Members                       *
// 3 -> Classes                       *
// 4 -> News                          *
//*************************************

// nzbot 7war el ids fi al a5er
void XFitGym::reorganizeGrid(QGridLayout* grid, QPushButton* addCard) {
    grid->removeWidget(addCard);

    QList<QWidget*> cards;
    for (int i = 0; i < grid->count(); ++i) {
        QWidget* widget = grid->itemAt(i)->widget();
        if (widget) {
            cards.append(widget);
        }
    }

    while (QLayoutItem* item = grid->takeAt(0)) {
        delete item;
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

void XFitGym::generateMemberCards(QScrollArea* scrollArea, QWidget* parent) {

    if (scrollArea->widget()) {
        QWidget* oldWidget = scrollArea->widget();
        scrollArea->takeWidget();
        oldWidget->deleteLater();
    }

    QWidget* scrollWidget = new QWidget();
    scrollWidget->setObjectName("scrollWidget");
    scrollWidget->setStyleSheet("QWidget#scrollWidget{background-color: #1e1e1e;}");

    QGridLayout* grid = new QGridLayout(scrollWidget);
    grid->setSpacing(20);
    grid->setContentsMargins(20, 20, 20, 20);

    QLayoutItem* item;
    while ((item = grid->takeAt(0)) != nullptr) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }

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
    int numMembers = Login::membersData.size();

    Manager man;
    Receptionist recep;
    QObject::connect(addCard, &QPushButton::clicked, parent, [=, &man, &recep]() {
        addMembers* addPage = new addMembers(parent);

        int screenWidth = 960;
        int screenHeight = 540;

        int x = (screenWidth - addPage->width()) / 2;
        int y = (screenHeight - addPage->height()) / 2;

        addPage->setWindowTitle("Add member");
        addPage->move(x, y);
        addPage->resize(400, 300);
        addPage->setWindowModality(Qt::ApplicationModal);
        addPage->show();

        addPage->ui.DOB->setInputMask("0000-00-00");

        QString id = QString::number(Login::membersData.size() + 1001);

        for (auto it : Login::membersData) {
            if (id == it.first) {
                int num = id.toInt();
                num++;
                id = QString::number(num);
            }

        }
        addPage->ui.ID->setText(id);


        addPage->ui.comboBox->addItem("Choose plan");
        addPage->ui.comboBox->addItem("Monthly");
        addPage->ui.comboBox->addItem("6-Months");
        addPage->ui.comboBox->addItem("Yearly");
        addPage->ui.comboBox->addItem("Yearly VIP");
        
        QObject::connect(addPage->ui.Submit, &QPushButton::clicked, parent, [=, &man, &recep]() {

            QString dob = addPage->ui.DOB->text();
            QStringList parts = dob.split('-');
            int year = 0;
            int month = 0;
            int day = 0;
            if (parts.size() == 3) {
                year = parts[0].toInt();
                month = parts[1].toInt();
                day = parts[2].toInt();

            }

            QDate date(year, month, day);
            bool check = (addPage->ui.comboBox->currentIndex() == 0 || addPage->ui.USERNAME->text().isEmpty() || addPage->ui.NAME->text().isEmpty() || addPage->ui.DOB->text().isEmpty()
                || !date.isValid() || year > QDate::currentDate().year());

            bool used = false;
            for (auto it : Login::membersData)
                if (addPage->ui.USERNAME->text().toLower() == it.second.getEmail().toLower())
                {
                    used = true;
                    break;
                }
            for (auto it : Staff::staffData)
                if (addPage->ui.USERNAME->text().toLower() == it.second.getEmail().toLower())
                {
                    used = true;
                    break;
                }
            if (check) {
                addPage->ui.message->setText("Invalid data");
                addPage->ui.message->setVisible(true);
                QTimer::singleShot(1250, addPage->ui.message, &QLabel::hide);
                return;
            }
            else if (used) {
                addPage->ui.message->setText("Used username");
                addPage->ui.message->setVisible(true);
                QTimer::singleShot(1250, addPage->ui.message, &QLabel::hide);
                return;
            }
            QString email = addPage->ui.USERNAME->text();
            QString name = addPage->ui.NAME->text();
            QString DateOFBirth = addPage->ui.DOB->text();
            QString plan = addPage->ui.comboBox->currentText();
            
            Customer c(id,email,name,DateOFBirth);
            c.sub.type = plan;
            c.sub.SetStartDate(*currentDate);
            Manager m;
            
            // add 
            if (plan.toLower() == "monthly")
            {
                Subscription::monthlyCounter++;
                Manager::totalSubFees += m.monthFee;
                c.sub.SetEndDate(currentDate->addMonths(1));
                c.sub.priceAfterDiscount = m.monthFee;

            }
            else if (plan.toLower() == "6-months")
            {
                Subscription::sixmonthlyCounter++;
                Manager::totalSubFees += m.sixmonthFee;
                c.sub.SetEndDate(currentDate->addMonths(6));
                c.sub.priceAfterDiscount = m.sixmonthFee;

            }
            else if (plan.toLower() == "yearly")
            {
                Subscription::yearlyCounter++;
                Manager::totalSubFees += m.yearFee;
                c.sub.SetEndDate(currentDate->addYears(1));
                c.sub.priceAfterDiscount = m.yearFee;

            }
            else if (plan.toLower() == "yearly vip")
            {
                Subscription::yearlyVIPCounter++;
                Manager::totalSubFees += m.VIPFee;
                c.sub.SetEndDate(currentDate->addYears(1));
                c.sub.priceAfterDiscount = m.VIPFee;
            }
            
            if (Login::isReceptionist) {
                Receptionist recep;
                recep.AddMember(c);
            }
            else {
                man.AddMember(c);
            }
            addPage->close();
            });
        });
    int i = 0;
    for (auto& user : Login::membersData) {
        QString name = user.second.getName();
        QString plan = user.second.sub.type;
        QString subscription;
        if(plan.toLower() == "monthly")
            subscription = "Ends: " + user.second.sub.endDate.toString("yyyy/MM/dd");
        else if(plan.toLower() == "6-months")
            subscription = "Ends: " + user.second.sub.endDate.toString("yyyy/MM/dd");
        else if(plan.toLower() == "yearly")
            subscription = "Ends: " + user.second.sub.endDate.toString("yyyy/MM/dd");
        else if (plan.toLower() == "yearly vip")
            subscription = "Ends: " + user.second.sub.endDate.toString("yyyy/MM/dd");

        Cards* card = new Cards(name, plan, subscription, scrollWidget);

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
        
        QString ID = user.first;
        QObject::connect(removeBtn, &QPushButton::clicked, parent, [=, &man, &recep]() {
            if (Login::isReceptionist)
                recep.RemoveMember(ID);
            else
                man.RemoveMember(ID);

            grid->removeWidget(card);
            card->deleteLater();
            reorganizeGrid(grid, addCard);
            });
        double* Total = new double();
        QString* Plan = new QString("");

        QObject::connect(renewBtn, &QPushButton::clicked, parent, [=, &man, &recep, &user]() {
            renewMembers* renewPage = new renewMembers(parent);

            int screenWidth = 960;
            int screenHeight = 540;

            int x = (screenWidth - renewPage->width()) / 2;
            int y = (screenHeight - renewPage->height()) / 2;

            renewPage->setWindowTitle("Subscription renewal");
            renewPage->move(x, y);
            renewPage->resize(400, 300);
            renewPage->setWindowModality(Qt::ApplicationModal);
            renewPage->show();
            renewPage->ui.Title->setText("Renew Subscription For " + name);
            QButtonGroup* group = new QButtonGroup(parent);
            group->setExclusive(true);

            group->addButton(renewPage->ui.Month);
            group->addButton(renewPage->ui.sixMonth);
            group->addButton(renewPage->ui.Year);
            group->addButton(renewPage->ui.YearVIP);

            QMap<QPushButton*, QPair<double, QString>> priceMap = {
            { renewPage->ui.Month,    {300, "Monthly"}},
            { renewPage->ui.sixMonth, {1200, "6-Months"}},
            { renewPage->ui.Year,     {2200, "Yearly"}},
            { renewPage->ui.YearVIP,  {4000, "Yearly VIP"} }
            };

            for (auto it = priceMap.begin(); it != priceMap.end(); ++it) {
                QPushButton* button = it.key();
                double price = it.value().first;
                QString pl = it.value().second;
                
                QObject::connect(button, &QPushButton::clicked, parent, [=, &user]() {
                    *Plan = pl;
                    Subscription sub;
                    double discount = sub.CalculatePrice(price, *currentDate, user.second.sub.endDate, user.second.sub.type);
                    double total = price - discount;
                    *Total = total;
                    renewPage->ui.subFees->setText(QString::number(price) + "$");
                    renewPage->ui.discount->setText(QString::number(discount) + "$");
                    renewPage->ui.totalFees->setText(QString::number(total) + "$");
                    });
            }

            QObject::connect(renewPage->ui.confirm, &QPushButton::clicked, parent, [=, &user]() {
                if (group->checkedButton() == nullptr) {
                    return;
                }

                if (Subscription::tenth) {
                    Manager::discountTenthCounter++;
                }
                else if (Subscription::half) {
                    Manager::discountHalfCounter++;
                }
                else if (Subscription::quarter) {
                    Manager::discountQuarterCounter++;
                }

                if (user.second.sub.type == "NoSubscription")
                {
                    
                    user.second.sub.type = *Plan;
                    user.second.sub.SetStartDate(*currentDate);

                    if (Plan->toLower() == "monthly") {
                        user.second.sub.endDate = currentDate->addMonths(1);
                    }
                    else if (Plan->toLower().toLower() == "6-months") {
                        user.second.sub.endDate = currentDate->addMonths(6);
                    }
                    else if (Plan->toLower().toLower() == "yearly") {
                        user.second.sub.endDate = currentDate->addYears(1);
                    }
                    else if (Plan->toLower().toLower() == "yearly vip") {
                        user.second.sub.endDate = currentDate->addYears(1);
                    }
                    user.second.sub.priceAfterDiscount = *Total;
                }

                else 
                {
                    if(Login::isReceptionist)
                    {
                        Receptionist recep;
                        recep.RenewSubscription(user.second.sub.endDate, *Plan, user.second.sub.type, *currentDate);
                    }
                    else
                    {
                        Manager man;
                        man.RenewSubscription(user.second.sub.endDate, *Plan, user.second.sub.type, *currentDate);
                    }
                }
                

                Manager::totalSubFees += *Total;

                renewPage->close();
                Subscription::tenth = false;
                Subscription::quarter = false;
                Subscription::half = false;
                });

            });
        i++;
    }

    int addRow = numMembers / 3;
    int addCol = numMembers % 3;
    grid->addWidget(addCard, addRow, addCol);

    if (scrollArea->widget()) {
        scrollArea->widget()->deleteLater();
    }
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);

}
void XFitGym::generateStaffCards(QScrollArea* scrollArea, QWidget* parent) {

    if (scrollArea->widget()) {
        QWidget* oldWidget = scrollArea->widget();
        scrollArea->takeWidget();
        oldWidget->deleteLater();
    }


    QWidget* scrollWidget = new QWidget();
    scrollWidget->setObjectName("scrollWidget");
    scrollWidget->setStyleSheet("QWidget#scrollWidget{background-color: #1e1e1e;}");

    QGridLayout* grid = new QGridLayout(scrollWidget);
    grid->setSpacing(20);
    grid->setContentsMargins(20, 20, 20, 20);

    QLayoutItem* item;
    while ((item = grid->takeAt(0)) != nullptr) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }

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

    Manager man;
    int numStaff = Staff::staffData.size();
    QObject::connect(addCard, &QPushButton::clicked, parent, [=,&numStaff, &man]() {
        addMembers* addPage = new addMembers(parent);
        
        int screenWidth = 960;
        int screenHeight = 540;

        int x = (screenWidth - addPage->width()) / 2;
        int y = (screenHeight - addPage->height()) / 2;

        addPage->setWindowTitle("Add staff");
        addPage->move(x, y);
        addPage->resize(400, 300);
        addPage->setWindowModality(Qt::ApplicationModal);
        addPage->show();

        addPage->ui.DOB->setInputMask("0000-00-00");
        addPage->ui.keyLabel->setText("Role");

        addPage->ui.comboBox->addItem("Choose role");
        addPage->ui.comboBox->addItem("Receptionist");
        addPage->ui.comboBox->addItem("Coach");

        QString id = QString::number(Staff::staffData.size() + 2001);
        for (auto it : Staff::staffData) {
            if (id == it.first) {
                int num = id.toInt();
                num++;
                id = QString::number(num);
            }
        }
        addPage->ui.ID->setText(id);


        QObject::connect(addPage->ui.Submit, &QPushButton::clicked, parent, [=,&numStaff, &man, &id]() {
            QString dob = addPage->ui.DOB->text();
            QStringList parts = dob.split('-');
            int year = 0;
            int month = 0;
            int day = 0;
            if (parts.size() == 3) {
                year = parts[0].toInt();
                month = parts[1].toInt();
                day = parts[2].toInt();

            }

            QDate date(year, month, day);
            bool check = (addPage->ui.comboBox->currentIndex() == 0 || addPage->ui.USERNAME->text().isEmpty() || addPage->ui.NAME->text().isEmpty() || addPage->ui.DOB->text().isEmpty()
                || !date.isValid() || year > QDate::currentDate().year());
            bool used = false;
            for (auto it : Login::membersData)
                if (addPage->ui.USERNAME->text().toLower() == it.second.getEmail().toLower() || addPage->ui.NAME->text().toLower() == it.second.getName().toLower())
                {
                    used = true;
                    break;
                }
            for (auto it : Staff::staffData)
                if (addPage->ui.USERNAME->text().toLower() == it.second.getEmail().toLower() || addPage->ui.NAME->text().toLower() == it.second.getName().toLower())
                {
                    used = true;
                    break;
                }
            if (check) {
                addPage->ui.message->setText("Invalid data");
                addPage->ui.message->setVisible(true);
                QTimer::singleShot(1250, addPage->ui.message, &QLabel::hide);
                return;
            }
            else if (used) {
                addPage->ui.message->setText("Used username");
                addPage->ui.message->setVisible(true);
                QTimer::singleShot(1250, addPage->ui.message, &QLabel::hide);
                return;
            }
            
            QString email = addPage->ui.USERNAME->text();
            QString name = addPage->ui.NAME->text();
            QString DateOFBirth = addPage->ui.DOB->text();
            QString role = addPage->ui.comboBox->currentText();
            if (role.toLower() == "coach") {
                Coach c(id, email, name, DateOFBirth, role);
                man.AddCoach(c);
            }
            else if (role.toLower() == "receptionist") {
                Receptionist r(id, email, name, DateOFBirth, role);
                man.AddReceptionist(r);
            }
            addPage->close();
            });
        });

    int i = 0;
    for (auto staff : Staff::staffData) {
        QString name = staff.second.getName();
        QString position = staff.second.role;
        Cards* staffCard = new Cards(name, position, "", scrollWidget);

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

        QString ID = staff.first;
        QString role = staff.second.role;
        QObject::connect(removeBtn, &QPushButton::clicked, parent, [=, &man]() {

            man.RemoveStaff(ID);
            grid->removeWidget(staffCard);
            staffCard->deleteLater();

            reorganizeGrid(grid, addCard);
            });
        i++;

    }

    int addRow = numStaff / 3;
    int addCol = numStaff % 3;
    grid->addWidget(addCard, addRow, addCol);

    if (scrollArea->widget()) {
        scrollArea->widget()->deleteLater();
    }
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);

}

// optimiiiiiiiiiiiiiiiize daroory
void XFitGym::simulateDay() {

    QDate currentDate = programClock->GetCurrentDate();
    qDebug() << "\n📅 Simulated Date:" << currentDate.toString("yyyy-MM-dd");

    // Subscription Deadline Check for all customers
    for (auto& c : Login::membersData) {
        int daysLeft = notifier->CheckSubscriptionDeadline(c.second.sub, currentDate);
        if (daysLeft <= 0) {
            if (!Notifications::notifications[c.first.toInt()].contains("Your Gym Membership Has Expired")) {
                Notifications::notifications[c.first.toInt()].push_back("Your Gym Membership Has Expired");
                qDebug() << "Notification for" << c.second.getName() << ": Your Gym Membership Has Expired";
                Login::membersData[log->ui.ID->text()].sub.type = "NoSubscription";
               
            }
        }
        else if (daysLeft <= 10) {
            QString message = "You Have " + QString::number(daysLeft) + " Days Left in Your Subscription";
            Notifications::notifications[c.first.toInt()].push_back(message);
            qDebug() << "Notification for" << c.second.getName() << ":" << message;
        }
    }

    // Check for all Training Sessions if Their date had passed
    for (auto it = Classes::allsessions.begin(); it != Classes::allsessions.end(); ) {
        // satr el minus
        int daysLeftSessions = currentDate.daysTo(it->second.date);
        if (daysLeftSessions < 0) {
            it = Classes::allsessions.erase(it);  // safe erase
        }
        else {
            ++it;
        }
    }

    // Check if a Training Session had passed and put it in the History
    for (auto& c : Login::membersData) {
        int sz = Login::membersData[c.first].bookedsessions.size();
        if (sz == 0) continue;

        for (int i = 0; i < sz; i++) {
            int daysLeftHistorySessions = currentDate.daysTo(Login::membersData[c.first].bookedsessions.front().date);
            TrainingSession tp = Login::membersData[c.first].bookedsessions.front();
            if (daysLeftHistorySessions < 0) {
                Login::membersData[c.first].historyTrainingSessions.push(tp);
                Login::membersData[c.first].bookedsessions.pop();
            }
            else {
                Login::membersData[c.first].bookedsessions.pop();
                Login::membersData[c.first].bookedsessions.push(tp);
            }
        }
    }

    // Attendance
    for (auto& c : Login::membersData) {
        if (usersLoggedInToday.count(c.second.getId())) {
            c.second.attendance.push_back(true);
        }
        else {
            c.second.attendance.push_back(false);
        }
    }
    if (Login::membersData.find(currentUserID) != Login::membersData.end()) {
        dash->setAttendance(daysSimulated, Login::membersData[currentUserID].attendance);
    }

    programClock->Tick();
    daysSimulated++;
    usersLoggedInToday.clear();
    
}
void XFitGym::simulateHour() {

    usersLoggedInToday.insert(currentUserID);

    // Increasing and Displaying hours
    int hourDisplay = simulatedHour % 12;
    if (hourDisplay == 0) hourDisplay = 12;
    QString ampm = (simulatedHour < 12) ? "AM" : "PM";
    QString hourText = QString("%1:00 %2").arg(hourDisplay, 2, 10, QChar('0')).arg(ampm);

    int hour = hourDisplay;
    if (ampm == "PM" && hour != 12) hour += 12;
    if (ampm == "AM" && hour == 12) hour = 0;

    timeText = new QTime(hour, 0); // This is equivalent to QTime(hour, 0)




    for (auto& a : Login::membersData)
    {
        for (auto& b : a.second.bookedCourt)
        {
            QString day = b.first.toString("ddd");
            QString time = b.second;

            if (day == *dayName) {
                int currentTime = timeText->hour();
                QString hourStr = time.split(":").first();
                int hour = hourStr.toInt() + 12;
                if (hour == 24)
                    hour = hourStr.toInt();
                int leftTime = hour - currentTime;
                qDebug() << "Current -> " << leftTime;


                if (leftTime <= 0) {
                    Login::membersData[user_Profile->ui.ID->text()].CancelPaddleCourt(b.first, time);
                    courtSlotButtons[{day, time}]->setStyleSheet("background-color: green;border: 1px solid gray;");
                    courtSlotButtons[{day, time}]->setEnabled(true);
                    padel->selectedSlot = nullptr;
                }
                else if (leftTime <= 3)
                {
                    QPushButton* cancelCourt = cancelCourtButtons.value({ b.first, time }, nullptr);
                    if (cancelCourt) {
                        cancelCourt->setEnabled(false);
                        cancelCourt->setStyleSheet(" QPushButton { background-color: grey; border: 1px solid grey; }");
                    }
                }
            }
        }

    }




    QDate simDate = programClock->GetCurrentDate().addDays(simulatedDay);
    currentDate = new QDate(simDate);

    dayName = new QString(simDate.toString("ddd")); // full day name
    QString dateText = simDate.toString("yyyy-MM-dd");
    QString fullText = dateText + " (" + *dayName + ")  " + hourText;

    home->ui.Date_time->setText(fullText);
    recep_home->ui.Date_time->setText(fullText);
    man_home->ui.Date_time->setText(fullText);
    coach_home->ui.Date_time->setText(fullText);

    simulatedHour++;
    if (simulatedHour >= 24) {
        simulatedHour = 0;
        simulateDay();
    }
}
XFitGym::XFitGym(QWidget* parent)
    : QMainWindow(parent)
{

    customers = CustomerLoader::LoadCustomersFromFile("CustomerData.txt");

    programClock = new ProgramClock();
    notifier = new Notifications();


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
    manprofile = new Staff_profile(this);
    coach_home = new Coach_homepage(this);
    coach_classes = new Coach_classes(this);
    coachprofile = new Staff_profile(this);
    recep_home = new Receptionist_homepage(this);
    recepprofile = new Staff_profile(this);
    recep_members = new Receptionist_members(this);
    recep_classes = new Receptionist_classes(this);
    recep_news = new Receptionist_news(this);
    Manager man;
    Receptionist recep;

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &XFitGym::simulateHour);
    timer->start(5000);  // 1 simulated hour = 0.5 real seconds

    ui.Main->addWidget(log);
    ui.Main->addWidget(home);
    ui.Main->addWidget(man_home);
    ui.Main->addWidget(coach_home);
    ui.Main->addWidget(recep_home);

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
    man_home->ui.Pages->addWidget(manprofile);

    coach_home->ui.Pages->addWidget(coachprofile);
    coach_home->ui.Pages->addWidget(coach_classes);

    recep_home->ui.Pages->addWidget(recepprofile);
    recep_home->ui.Pages->addWidget(recep_members);
    recep_home->ui.Pages->addWidget(recep_classes);
    recep_home->ui.Pages->addWidget(recep_news);

    // just for the show password functionality 
    QIcon show = QIcon("assets/showPassword.png");
    QIcon hide = QIcon("assets/hidePassword.png");
    log->ui.ID->setMaxLength(30);
    log->ui.warning->setVisible(false);

    connect(log->ui.Login, &QPushButton::clicked, this, [=]() {

        QString username = log->ui.Email->text();
        QString id = log->ui.ID->text();

        if (username == "manager" && id == "1") {
            currentUserID = "1";
            ui.Main->setCurrentIndex(2); 
            man_home->ui.welcome->setText("Welcome Back, Manager");
            manprofile->ui.ID->setText(id);
            manprofile->ui.Name->setText("XFitGym Manager");
            manprofile->ui.DOB->setText("2004/12/13");
            return;
        }
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

        else if (Login::isCoach) {
            currentUserID = Staff::staffData[id].getId();
            ui.Main->setCurrentIndex(3);
            coach_home->ui.welcome->setText("Welcome Back, Coach");
            coachprofile->ui.ID->setText(id);
            coachprofile->ui.Name->setText(Staff::staffData[id].getName());
            coachprofile->ui.DOB->setText(Staff::staffData[id].getDateOfBirth());
            coachprofile->ui.Role->setText(Staff::staffData[id].role);
            Login::isCoach = false;
            Login::isStaff = false;
            return;
        }
        else if (Login::isReceptionist) {
            currentUserID = Staff::staffData[id].getId();
            ui.Main->setCurrentIndex(4);
            recepprofile->ui.ID->setText(id);
            recepprofile->ui.Name->setText(Staff::staffData[id].getName());
            recepprofile->ui.DOB->setText(Staff::staffData[id].getDateOfBirth());
            recepprofile->ui.Role->setText(Staff::staffData[id].role);
            recep_home->ui.welcome->setText("Welcome Back, Receptionist");
            Login::isReceptionist = false;
            Login::isStaff = false;
            return;
        }
        else
        {
            currentUserID = Login::membersData[id].getId();
            user_Profile->ui.ID->setText(Login::membersData[id].getId());
            user_Profile->ui.Name->setText(Login::membersData[id].getName());
            user_Profile->ui.DOB->setText(Login::membersData[id].getDateOfBirth());
            if (Login::membersData[id].sub.type.isEmpty()) {
                Login::membersData[id].sub.type = "NoSubscription";
                user_Profile->ui.Plan->setText("No Subscription");

            }
            else
            {
                user_Profile->ui.Plan->setText(Login::membersData[id].sub.type);
            }
            home->ui.welcome->setText("Welcome Back, " + Login::membersData[id].getName());

            ui.Main->setCurrentIndex(1);

            log->ui.showPassword->setIcon(hide);
            log->ui.ID->setEchoMode(QLineEdit::Password);
            Login::isMember = false;
        }
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

    // padel gauges
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
    int* Pvalue = new int(0);
    int* Cvalue = new int(0);
    int currentCourtSize = Login::membersData[user_Profile->ui.ID->text()].bookedCourt.size();
    if (currentCourtSize > *Pvalue)
        *Pvalue = currentCourtSize;
    QString Pval = QString::number(*Pvalue);
    dash->ui.PCounter->setText(Pval);
    Pgauge->setValue(*Pvalue);

    int currentSessionSize = Login::membersData[user_Profile->ui.ID->text()].bookedsessions.size();
    if (currentSessionSize > *Cvalue)
        *Cvalue = currentSessionSize;

    QString Cval = QString::number(*Cvalue);
    dash->ui.CCounter->setText(Cval);
    Cgauge->setValue(*Cvalue);

    connect(home->ui.Dashboard, &QPushButton::clicked, this, [=]() {


        if (Login::membersData[user_Profile->ui.ID->text()].historyTrainingSessions.empty())
        {
            setScrolltoTop();
            dash->ui.message->setVisible(true);
            home->ui.Pages->setCurrentIndex(2);
            return;
        }
        else {
            dash->ui.message->setVisible(false);
        }
        //dynamically generating the past workouts

        QWidget* pastWorkouts = new QWidget;
        pastWorkouts->setStyleSheet("background-color: #1e1e1e; color: white;");

        QVBoxLayout* layout = new QVBoxLayout(pastWorkouts);
        layout->setAlignment(Qt::AlignTop);
        layout->setContentsMargins(10, 10, 10, 10);
        layout->setSpacing(10);

            stack<TrainingSession> temp = Login::membersData[user_Profile->ui.ID->text()].historyTrainingSessions;
            while(!temp.empty()) {
              
                TrainingSession trTop = temp.top();

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

                QLabel* className = new QLabel(trTop.name, workouts);
                className->setStyleSheet("color: white;font-family: 'Futura'; font-weight: bold; font-size: 14pt; background: transparent;");
                className->adjustSize();
                className->move(15, 10);

                QLabel* coach = new QLabel(trTop.coachname, workouts);
                coach->setStyleSheet("color: white;font-family: 'DM Serif Display'; font-size: 10pt; background: transparent;");
                coach->adjustSize();
                coach->move(15, className->y() + className->height() + 5);



                QString datee = trTop.date.toString("yyyy-MM-dd");

                QLabel* date = new QLabel(datee + "    " + trTop.time, workouts);
                date->setStyleSheet("color: #CCCCCC;font-family: 'DM Serif Display'; font-size: 10pt; background: transparent;");
                date->adjustSize();

            QTimer::singleShot(0, [=]() {
                int w = workouts->width();
                int h = workouts->height();
                date->move((w - date->width()) / 2 + 35, coach->y());
                });


                temp.pop();
          
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

           
        int i = 0;
        for (auto a:Classes::allsessions) {
            QString className = a.second.name;
            QString date_time = a.second.date.toString("yyyy-MM-dd")+"    "+a.second.time;
            QString coachName = "Coach: " + a.second.coachname;
            int attend = a.second.size;
            int max = a.second.capacity;

            Cards* card = new Cards(className, date_time, coachName, attend, max);
            QPushButton* waitlist = new QPushButton("Waitlist");
            QPushButton* book = new QPushButton("Book");
            //************************
            //  replace true with (attendedCounter < maxSize)
            if (attend < max)
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
                if (Login::membersData[user_Profile->ui.ID->text()].sub.type.toLower() == "yearly vip")
                {
                    Classes::allsessions[a.first].WaitlistIds.push_front(user_Profile->ui.ID->text().toInt());
                }
                Classes::allsessions[a.first].WaitlistIds.push_back(user_Profile->ui.ID->text().toInt());
                qDebug() << Classes::allsessions[a.first].WaitlistIds.back();
                int size = Classes::allsessions[a.first].WaitlistIds.size();
                set <int>check;
                for (auto b: Classes::allsessions[a.first].WaitlistIds)
                {
                    check.insert(b);
                }
                if (check.size() != size) 
                {
                    Classes::allsessions[a.first].WaitlistIds.pop_back();
                }

                });
            QObject::connect(book, &QPushButton::clicked, [=]() {
                TrainingSession tr = a.second;
                Login::membersData[user_Profile->ui.ID->text()].AddTrainingSession(tr);
                TrainingSession::sessionsCounter++;
                queue<TrainingSession> bookedsession = Login::membersData[user_Profile->ui.ID->text()].bookedsessions;
                set<int>checkin;
                int size = bookedsession.size();
                while (!bookedsession.empty()) 
                {
                    checkin.insert(bookedsession.front().id);
                    bookedsession.pop();
                }
                if (checkin.size() != size)
                {
                    Login::membersData[user_Profile->ui.ID->text()].CancelTrainingSession(a.first);
                }

                });
            i++;
        }

        scrollWidget->setLayout(grid);
        classes->ui.scrollArea->setWidget(scrollWidget);
        classes->ui.scrollArea->setWidgetResizable(true);


        home->ui.Pages->setCurrentIndex(6);
        });
    QStringList days = { "Sat", "Sun", "Mon", "Tue", "Wed","Thu" , "Fri" };
    QStringList times = { "12:00 PM", "1:00 PM", "2:00 PM", "3:00 PM", "4:00 PM", "5:00 PM", "6:00 PM", "7:00 PM", "8:00 PM" };
    connect(home->ui.Courts, &QPushButton::clicked, this, [=]() {
        setScrolltoTop();
        qDebug() << "Padel Courts";

        // Clean previous state
        padel->selectedSlot = nullptr;

        // 1. Delete existing layout and widgets in padel->ui.widget
        if (padel->ui.widget->layout()) {
            QLayout* oldLayout = padel->ui.widget->layout();
            QLayoutItem* item;
            while ((item = oldLayout->takeAt(0)) != nullptr) {
                delete item->widget();  // Delete the widget
                delete item;            // Delete the layout item
            }
            delete oldLayout;  // Delete the old layout itself
        }
        courtSlotButtons.clear();

        // 2. Create new grid directly in padel->ui.widget
        QGridLayout* grid = new QGridLayout(padel->ui.widget);
        grid->setContentsMargins(0, 0, 0, 0);  // Remove default margins
        grid->setSpacing(0);  // Adjust spacing as needed

        int courtCount = 7;

        // Headers for weekdays (Mon, Tue, ..., Sun)
        for (int d = 0; d < days.size(); ++d) {
            QLabel* dayLabel = new QLabel(days[d], padel->ui.widget);
            dayLabel->setAlignment(Qt::AlignCenter);
            grid->addWidget(dayLabel, 0, d + 1);
        }

        // Time slots on the left
        for (int t = 0; t < times.size(); ++t) {
            QLabel* timeLabel = new QLabel(times[t], padel->ui.widget);
            timeLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
            grid->addWidget(timeLabel, t + 1, 0);
        }

        // Slots for court bookings
        for (int t = 0; t < times.size(); t++) {
            for (int c = 0; c < courtCount; c++) {
                QPushButton* slot = new QPushButton(padel->ui.widget);
                slot->setFixedSize(60, 40);
                slot->setStyleSheet("background-color: green; border: 1px solid gray;");

                for (auto a : Login::membersData) {
                    for (auto b : a.second.bookedCourt) {
                        QString day = b.first.toString("ddd");
                        QString time = b.second;
                        if (day == days[c] && time == times[t]) {
                            slot->setStyleSheet("background-color: red;border: 1px solid gray;");
                            slot->setEnabled(false);
                        }
                    }
                }

                grid->addWidget(slot, t + 1, c + 1);
                QObject::connect(slot, &QPushButton::clicked, [=]() mutable {
                    if (padel->selectedSlot) {
                        padel->selectedSlot->setStyleSheet("background-color: green;border: 1px solid gray;");
                    }
                    padel->selectedSlot = slot;
                    padel->selectedDay = days[c];
                    padel->selectedTime = times[t];
                    slot->setStyleSheet("background-color: yellow;border: 1px solid gray;");
                    });
                courtSlotButtons[{days[c], times[t]}] = slot;
            }
        }

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
            padel->ui.firstPlayers->setText(padel->competitors[0].second);
            padel->ui.firstScore->setText(QString::number(padel->competitors[0].first));
            padel->ui.secondPlayers->setText(padel->competitors[1].second);
            padel->ui.secondScore->setText(QString::number(padel->competitors[1].first));
            padel->ui.thirdPlayers->setText(padel->competitors[2].second);
            padel->ui.thirdScore->setText(QString::number(padel->competitors[2].first));
           


            home->ui.Pages->setCurrentIndex(7);
            });
    connect(home->ui.Feedback, &QPushButton::clicked, this, [=]() {
        setScrolltoTop();
        home->ui.Pages->setCurrentIndex(5);
        qDebug() << "Feedback";
        });
    connect(home->ui.Profile, &QPushButton::clicked, this, [=]() {
        setScrolltoTop();
        vector <pair<QDate, QString>> bookedCourts = Login::membersData[user_Profile->ui.ID->text()].bookedCourt;
        queue<TrainingSession>bookedsession = Login::membersData[user_Profile->ui.ID->text()].bookedsessions;


    //change true with (class.empty && courts.empty) .. w e3mel condition di lw7dha w di lw7dha
    if (bookedsession.empty()) {
        user_Profile->ui.messageClass->setVisible(true);
        home->ui.Pages->setCurrentIndex(3);
        QLayout* layout = user_Profile->ui.scrollAreaWidgetContents->layout();
        delete user_Profile->ui.scrollAreaClass->widget();
                
    }
    else
    {
        user_Profile->ui.messageClass->setVisible(false);
    }
    if (bookedCourts.empty()) {
        user_Profile->ui.messageCourt->setVisible(true);
        home->ui.Pages->setCurrentIndex(3);
        QLayout* layout = user_Profile->ui.scrollAreaWidgetContents->layout();
        delete user_Profile->ui.scrollAreaCourt->widget();
                
    }
    else
    {
        user_Profile->ui.messageCourt->setVisible(false);
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

        QLabel* className = new QLabel(bookedsession.front().name, activeClass);
        className->setStyleSheet("color: white;font-family: 'Futura'; font-weight: bold; font-size: 14pt; background: transparent;");
        className->adjustSize();
        className->move(15, 10);

        QLabel* coach = new QLabel(bookedsession.front().coachname, activeClass);
        coach->setStyleSheet("color: white;font-family: 'DM Serif Display'; font-size: 10pt; background: transparent;");
        coach->adjustSize();
        coach->move(15, className->y() + className->height() + 5);  // just below class name


        QLabel* ID = new QLabel(QString::number(bookedsession.front().id), activeClass);
        ID->setStyleSheet("color: #CCCCCC;font-family: 'DM Serif Display'; font-size: 10pt; background: transparent;");
        ID->adjustSize();
        ID->move(coach->x() + coach->width() + 50, coach->y());
               
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
            TrainingSession::sessionsCounter--;
            Login::membersData[log->ui.ID->text()].CancelTrainingSession(ID->text().toInt());
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

    for (auto a: bookedCourts) {
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

        QLabel* court = new QLabel("Paddel Court", activeCourt);
        court->setStyleSheet("color: white;font-family: 'Futura'; font-weight: bold; font-size: 14pt; background: transparent;");
        court->adjustSize();
        court->move(15, 10);

        QString day = a.first.toString("ddd");
        QString time = a.second;
        QLabel* date = new QLabel(day+"    "+time, activeCourt);
        date->setStyleSheet("color: #CCCCCC;font-family: 'DM Serif Display'; font-size: 10pt; background: transparent;");
        date->adjustSize();

        QPushButton* cancelCourt = new QPushButton("Cancel", activeCourt);
        if (true)
        {
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
        }

        cancelCourtButtons[{a.first, a.second}] = cancelCourt;

        cancelCourt->adjustSize();
        QTimer::singleShot(0, [=]() {
            int w = activeCourt->width();
            cancelCourt->move(w - cancelCourt->width() - 15, 20);
            });


        QTimer::singleShot(0, [=]() {
            int w = activeCourt->width();
            int h = activeCourt->height();
            date->move((w - date->width()) / 2 + 15, court->y() + court->height() + 5);
            });

        layoutCourt->addWidget(activeCourt);

        QObject::connect(cancelCourt, &QPushButton::clicked, [=]() {
            Login::membersData[user_Profile->ui.ID->text()].CancelPaddleCourt(a.first,time);

            Padel::courtsCounter--;
            courtSlotButtons[{day, time}]->setStyleSheet("background-color: green;border: 1px solid gray;");
            courtSlotButtons[{day, time}]->setEnabled(true);
            padel->selectedSlot = nullptr;
            activeCourt->deleteLater();
                });


        for (auto& a : Login::membersData)
        {
            for (auto& b : a.second.bookedCourt)
            {
                QString day = b.first.toString("ddd");
                QString time = b.second;

                if (day == *dayName) {
                    int currentTime = timeText->hour();
                    QString hourStr = time.split(":").first();
                    int hour = hourStr.toInt() + 12;
                    if (hour == 24)
                        hour = hourStr.toInt();
                    int leftTime = hour - currentTime;

                    if (leftTime <= 0) {
                        Login::membersData[user_Profile->ui.ID->text()].CancelPaddleCourt(b.first, time);
                        courtSlotButtons[{day, time}]->setStyleSheet("background-color: green;border: 1px solid gray;");
                        courtSlotButtons[{day, time}]->setEnabled(true);
                        padel->selectedSlot = nullptr;
                    }
                    else if (leftTime <= 3)
                    {
                        cancelCourt->setEnabled(false);
                        cancelCourt->setStyleSheet(" QPushButton { background-color: grey; border: 1px solid grey; }");
                    }
                }
            }

        }
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
        dash->clearAttendanceGui();
        currentUserID.clear();
        });

    // manager homepage control panel
    connect(man_home->ui.Dashboard, &QPushButton::clicked, this, [=]() {
        man_dash->ui.sixMonthCounter->setText(QString::number(Subscription::sixmonthlyCounter));
        man_dash->ui.MonthCounter->setText(QString::number(Subscription::monthlyCounter));
        man_dash->ui.YearCounter->setText(QString::number(Subscription::yearlyCounter));
        man_dash->ui.VIPCounter->setText(QString::number(Subscription::yearlyVIPCounter));

        man_dash->ui.halfCounter->setText(QString::number(Manager::discountHalfCounter));
        man_dash->ui.quarterCounter->setText(QString::number(Manager::discountQuarterCounter));
        man_dash->ui.tenthCounter->setText(QString::number(Manager::discountTenthCounter));

         
        man_dash->ui.coachSalCount->setText(QString::number(Coach::coachData.size() * man.coachSal));
        double coachSal = man_dash->ui.coachSalCount->text().toDouble();
        man_dash->ui.recepSalCount->setText(QString::number( (Staff::staffData.size() - Coach::coachData.size()) * man.recepSal));
        double recepSal = man_dash->ui.recepSalCount->text().toDouble();
        man_dash->ui.classesFeesCount->setText(QString::number(TrainingSession::sessionsCounter * man.classFees));
        double classFees = man_dash->ui.classesFeesCount->text().toDouble();
        man_dash->ui.padelFeesCount->setText(QString::number(Padel::courtsCounter * man.courtFees));
        double courtFees = man_dash->ui.padelFeesCount->text().toDouble();
        man_dash->ui.subFeesCount->setText(QString::number(Manager::totalSubFees));
        double subFee = man_dash->ui.subFeesCount->text().toDouble();

        man_dash->ui.ProfitCount->setText(QString::number(subFee + courtFees + classFees - recepSal - coachSal));

        qDebug() << Manager::totalSubFees;
        man_home->ui.Pages->setCurrentIndex(1);
        });
    connect(man_home->ui.Staff, &QPushButton::clicked, this, [=]() {

        generateStaffCards(man_staff->ui.scrollArea, this);
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
    connect(man_home->ui.Profile, &QPushButton::clicked, this, [=]() {
        man_home->ui.Pages->setCurrentIndex(6);
        });
    connect(man_home->ui.Logout, &QPushButton::clicked, this, [=]() {
        log->ui.Email->setText("");
        log->ui.ID->setText("");
        setScrolltoTop();
        man_home->ui.Pages->setCurrentIndex(0);
        ui.Main->setCurrentIndex(0);
        });
    connect(man_home->ui.Members, &QPushButton::clicked, this, [=]() {
        generateMemberCards(man_members->ui.scrollArea, this);
        man_home->ui.Pages->setCurrentIndex(2);
    });
    
    //coach homepage control panel
    connect(coach_home->ui.MyClasses, &QPushButton::clicked, this, [=]() {
        QWidget* scrollWidget = new QWidget();
        scrollWidget->setObjectName("scrollWidget");
        scrollWidget->setStyleSheet("QWidget#scrollWidget{background-color: #1e1e1e;}");

        QGridLayout* grid = new QGridLayout(scrollWidget);
        grid->setSpacing(20);
        grid->setContentsMargins(20, 20, 20, 20);

        int numStaff = Classes::tempallsessions.size();
        QList<Cards*> classCards;
        int i = 0;
        for (auto session : Classes::tempallsessions) {
            if(session.second.coachname == coachprofile->ui.Name->text())
            {
                QString className = session.second.name;
                QString date_time = session.second.date.toString() + "   " + session.second.time;
                QString coachName = session.second.coachname;
                int attend = session.second.size;
                int max = session.second.capacity;

                Cards* classCard = new Cards(className, date_time, coachName, attend, max, scrollWidget);
                classCards.append(classCard);

                QPushButton* cancelBtn = new QPushButton("Cancel", classCard);
                cancelBtn->setStyleSheet(R"(
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
        QPushButton:pressed {
            background-color: #C62828;
        }
    )");

                classCard->buttonLayout->addWidget(cancelBtn);

                int row = i / 3;
                int col = i % 3;
                grid->addWidget(classCard, row, col);

                connect(cancelBtn, &QPushButton::clicked, this, [=]() {

                    coach->CancelSession(session.second.id);
                    grid->removeWidget(classCard);
                    classCard->deleteLater();
                    reorganizeGrid(grid, nullptr);
                    });
                i++;
            }
        }

        if (coach_classes->ui.scrollArea->widget()) {
            coach_classes->ui.scrollArea->widget()->deleteLater();
        }

        coach_classes->ui.scrollArea->setWidget(scrollWidget);
        classes->ui.scrollArea->setWidgetResizable(true);
        coach_home->ui.Pages->setCurrentIndex(2);
        });
    connect(coach_home->ui.Profile, &QPushButton::clicked, this, [=]() {
        coach_home->ui.Pages->setCurrentIndex(1);
        });
    connect(coach_home->ui.Logout, &QPushButton::clicked, this, [=]() {
        log->ui.Email->setText("");
        log->ui.ID->setText("");
        setScrolltoTop();
        coach_home->ui.Pages->setCurrentIndex(0);
        ui.Main->setCurrentIndex(0);


        });

    //receptionist homepage control panel
    connect(recep_home->ui.Members, &QPushButton::clicked, this, [=]() {
        Login::isReceptionist = true;
        generateMemberCards(recep_members->ui.scrollArea, this);
        recep_home->ui.Pages->setCurrentIndex(2);
        });
    connect(recep_home->ui.Classes, &QPushButton::clicked, this, [=]() {
        
        recep_classes->ui.coachNames->clear();
        recep_classes->ui.coachNames->addItem("Choose coach");
        for (auto coach : Coach::coachData)
        {
            recep_classes->ui.coachNames->addItem(coach.second.getName());
        }
        //recep_classes->ui.dateTime->setMinimumDate(QDate::currentDate());
        recep_classes->ui.className->setMaxLength(20);
        recep_classes->ui.classCapacity->setValidator(new QIntValidator(0, 999, this));
        recep_home->ui.Pages->setCurrentIndex(3);
    });
    connect(recep_home->ui.News, &QPushButton::clicked, this, [=]() {
        recep_home->ui.Pages->setCurrentIndex(4);

    });
    connect(recep_home->ui.Profile, &QPushButton::clicked, this, [=]() {
        recep_home->ui.Pages->setCurrentIndex(1);
    });
    connect(recep_home->ui.Logout, &QPushButton::clicked, this, [=]() {
        log->ui.Email->setText("");
        log->ui.ID->setText("");
        setScrolltoTop();
        recep_home->ui.Pages->setCurrentIndex(0);
        ui.Main->setCurrentIndex(0);
        Login::isReceptionist = false;

        });

    //inner buttons
    connect(user_Profile->ui.viewPlans, &QPushButton::clicked, this, [=]() {
        home->ui.Pages->setCurrentIndex(1);
        });
    connect(user_Profile->ui.Cancel, &QPushButton::clicked, this, [=]() {
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
            Login::membersData[user_Profile->ui.ID->text()].AddCourtBooking(padel->selectedDay, padel->selectedTime);
            padel->selectedSlot->setStyleSheet("background-color: red;border: 1px solid gray;");
            padel->selectedSlot->setEnabled(false);
            courtSlotButtons[{padel->selectedDay, padel->selectedTime}] = padel->selectedSlot;
            padel->selectedSlot = nullptr;
            Padel::courtsCounter++;
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
        QString thirdTeam_firstName = man_tournaments->ui.TFname->text();
        QString thirdTeam_secondName = man_tournaments->ui.TSname->text();
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
             
            
             padel->competitors[0].first = firstScore.toInt();
             padel->competitors[0].second = firstTeam_firstName+ " & " + firstTeam_secondName;
             padel->competitors[1].first = secondScore.toInt();
             padel->competitors[1].second = secondTeam_firstName + " & " + secondTeam_secondName;
             padel->competitors[2].first = thirdScore.toInt();
             padel->competitors[2].second = thirdTeam_firstName + " & " + thirdTeam_secondName;
            
            sort(padel->competitors.rbegin(), padel->competitors.rend());

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
    connect(recep_classes->ui.confirm, &QPushButton::clicked, this, [=, &recep]() {

        if (recep_classes->ui.coachNames->currentIndex() == 0 || recep_classes->ui.className->text().isEmpty() || recep_classes->ui.classCapacity->text().isEmpty()) {
            return;
        }

        QString coachName = recep_classes->ui.coachNames->currentText();
        QString className = recep_classes->ui.className->text();
        int classCapacity = recep_classes->ui.classCapacity->text().toInt();
        QDate classDate = recep_classes->ui.dateTime->date();
        QString classTime = recep_classes->ui.dateTime->time().toString("hh:mm AP");
        int classID =  2001 + Classes::tempallsessions.size();
        int classSize = 0;
        TrainingSession tr(classID, className, classCapacity, classSize, coachName, classDate, classTime);

        recep.CreateClass(classID, tr);

        recep_classes->ui.coachNames->setCurrentIndex(0);
        recep_classes->ui.classCapacity->clear();
        recep_classes->ui.className->clear();
        recep_classes->ui.dateTime->setDateTime(recep_classes->ui.dateTime->minimumDateTime());

        });
    connect(recep_news->ui.submit, &QPushButton::clicked, this, [=, &recep]() {
        QString news = recep_news->ui.News->toPlainText();
        QString image = recep_news->relativePath;

        recep.AddNews(news, image);

        recep_news->ui.News->clear();
        recep_news->ui.image->clear();

    });
}
XFitGym::~XFitGym()
{
    log = nullptr;
    dash = nullptr;
    Pgauge = nullptr;
    Cgauge = nullptr;
    home = nullptr;
    user_Profile = nullptr;
    notifications = nullptr;
    feedback = nullptr;
    classes = nullptr;
    padel = nullptr;
    man_home = nullptr;
    man_dash = nullptr;
    man_members = nullptr;
    man_staff = nullptr;
    man_tournaments = nullptr;
    man_feedback = nullptr;
    renewPage = nullptr;
    addPage = nullptr;
    manprofile = nullptr;
    coachprofile = nullptr;
    recepprofile = nullptr;
    coach_home = nullptr;
    coach_classes = nullptr;
    recep_home = nullptr;
    recep_members = nullptr;
    recep_classes = nullptr;
    recep_news = nullptr;
    staff = nullptr;
    coach = nullptr;

    for (auto it = courtSlotButtons.begin(); it != courtSlotButtons.end(); ++it) {
        delete it.value();
    }
    courtSlotButtons.clear();
}

void XFitGym::setScrolltoTop()
{
    user_Profile->ui.scrollArea->verticalScrollBar()->setValue(0);
    notifications->ui.scrollArea->verticalScrollBar()->setValue(0);
    dash->ui.scrollArea->verticalScrollBar()->setValue(0);
}
void XFitGym::save()
{
    padel->savecompetitors();
    classes->savesession();
    notifications->saveNotifications();
    feedback->saveFeedBack();
    log->saveData();
    padel->savenews();
    staff->SaveStaffData();
}
void XFitGym::load()
{
    padel->loadcompetitors();
    classes->loadsession();
    notifications->loadNotifications();
    feedback->loadFeedBack();
    padel->loadnews();
    staff->LoadStaffData();
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

    titleLabel->setStyleSheet("font-size: 13pt; font-family: 'Futura'; color: white;");
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
