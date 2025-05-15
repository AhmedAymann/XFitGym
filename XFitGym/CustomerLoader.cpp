#include "CustomerLoader.h"
#include "Classes.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "Classes.h"



map<QString,Customer> CustomerLoader::LoadCustomersFromFile(const QString& filename)
{
    map<QString, Customer> customers;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "⚠️ Cannot open file:" << filename;
        return customers;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList mainParts = line.split('|');
        if (mainParts.size() < 1) continue;

        QStringList baseFields = mainParts[0].split(',');

        if (baseFields.size() < 4) {
            qWarning() << "⚠️ Invalid customer record:" << line;
            continue;
        }

        QString id = baseFields[0];
        QString email = baseFields[1];
        QString name = baseFields[2];
        QString dob = baseFields[3];

        Customer c(id, email, name, dob);

        int index = 4;

        // Handle Subscription
        if (baseFields.size() > index && baseFields[index] != "NoSubscription") {
            QString type = baseFields[index++];
            QString startDate = baseFields[index++];
            QString endDate = baseFields[index++];
            int price = baseFields[index++].toInt();

            c.sub.type = type;
            c.sub.startDate = startDate;
            c.sub.endDate = endDate;
            c.sub.priceAfterDiscount = price;
        }
        else {
            c.sub.type = "NoSubscription";
            ++index;
        }

        // Handle Court Bookings
        if (mainParts.size() >= 2 && mainParts[1] != "NoCourtBookings") {
            QStringList courtEntries = mainParts[1].split(';');
            for (const QString& entry : courtEntries) {
                QStringList fields = entry.split(',');
                if (fields.size() == 2) {
                    QDate date = QDate::fromString(fields[0], "yyyy-MM-dd");
                    QString dayName = date.toString("ddd");  
                    qDebug() << dayName;
                    QString time = fields[1];
                    c.AddCourtBooking(dayName, time);
                }
            }
        }

        // Handle Training Sessions
        if (mainParts.size() >= 3 && mainParts[2] != "NoTrainingSessions") {
            QStringList sessionEntries = mainParts[2].split(';');
            for (const QString& entry : sessionEntries) {
                QStringList fields = entry.split(',');
                if (fields.size() == 5) {
                    TrainingSession ts;
                    ts.name = fields[0];
                    ts.coachname = fields[1];
                    ts.date = QDate::fromString(fields[2], "yyyy-MM-dd");
                    ts.time = fields[3];
                    ts.id = fields[4].toInt();

                    c.AddTrainingSession(ts);
                    Classes::allsessions[ts.id].size--;
                }
            }
        }

        customers[id]=c;
    }

    return customers;
}