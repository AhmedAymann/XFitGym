#include "CustomerLoader.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

QVector<Customer> CustomerLoader::LoadCustomersFromFile(const QString& filename)
{
    QVector<Customer> customers;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "⚠️ Cannot open file:" << filename;
        return customers;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split(',');

        if (parts.size() < 4) {
            qWarning() << "⚠️ Invalid customer record:" << line;
            continue;
        }

        QString id = parts[0];
        QString email = parts[1];
        QString name = parts[2];
        QString dob = parts[3];

        Customer c(id, email, name, dob);

        int index = 4;

        // Subscription
        if (index < parts.size() && parts[index] != "NoSubscription") {
            QString type = parts[index++];
            QString startDate = (index < parts.size()) ? parts[index++] : "";
            QString endDate = (index < parts.size()) ? parts[index++] : "";
            int price = (index < parts.size()) ? parts[index++].toInt() : 0;

            c.sub.type = type;
            c.sub.startDate = startDate;
            c.sub.endDate = endDate;
            c.sub.priceAfterDiscount = price;
        }
        else {
            ++index; // Skip "NoSubscription"
        }

        // Paddle Court Bookings
        if (index < parts.size() && parts[index] != "NoCourtBookings") {
            while (index + 1 < parts.size() && parts[index] != "NoTrainingSessions") {
                QDate date = QDate::fromString(parts[index++], "yyyy-MM-dd");
                QString time = parts[index++];
                c.AddCourtBooking(date, time);
            }
        }
        else {
            ++index; // Skip "NoCourtBookings"
        }

        // Training Sessions
        if (index < parts.size()) {
            while (index + 3 < parts.size()) {
                QString sessionName = parts[index++];
                QString coachName = parts[index++];
                QDate date = QDate::fromString(parts[index++], "yyyy-MM-dd");
                QString time = parts[index++];

                TrainingSession session;
                session.name = sessionName.toStdString();
                session.coachname = coachName;
                session.date = date;
                session.time = time;

                //c.AddTrainingSession(session);
            }
        }

        customers.append(c);
    }

    return customers;
}