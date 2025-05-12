#pragma once
#include <QDate>
#ifndef PROGRAMCLOCK_H
#define PROGRAMCLOCK_H

//#include "Customer.h"

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
