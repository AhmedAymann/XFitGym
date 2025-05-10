#pragma once
#include <QDate>
#ifndef PROGRAMCLOCK_H
#define PROGRAMCLOCK_H

#include <QDate>

class ProgramClock
{
private:
    QDate currentDate;

public:
    ProgramClock();
    void Tick();
    QDate GetCurrentDate() const;
};

#endif // PROGRAMCLOCK_H
