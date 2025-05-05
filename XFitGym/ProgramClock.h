#pragma once
#include <QDate>

class ProgramClock
{
public:
    QDate currentDate;

    ProgramClock();
    void Tick(); // Simulate one day passing
    QDate GetCurrentDate() const;
};