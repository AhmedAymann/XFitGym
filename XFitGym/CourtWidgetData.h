#pragma once
#ifndef COURTWIDGETDATA_H
#define COURTWIDGETDATA_H

#include <QPushButton>
#include <QDate>
#include <QString>

struct CourtWidgetData {
    QDate bookingDate;
    QString timeSlot;
    QPushButton* cancelButton;



    // Optional: Add a constructor if you still have issues
    CourtWidgetData(QDate date, QString time, QPushButton* button)
        : bookingDate(date), timeSlot(time), cancelButton(button) {
    }
};

#endif // COURTWIDGETDATA_H






//put the training session passed in the history stack 
// remove the passed training session from the bookedsessions queue 
// remove passes trainingsession from the Sessions txt file (from the vector its stored in)