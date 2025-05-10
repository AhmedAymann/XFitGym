#include "ProgramClock.h"

ProgramClock::ProgramClock()
{
    currentDate = QDate::currentDate();
}

void ProgramClock::Tick()
{
    currentDate = currentDate.addDays(1);
}

QDate ProgramClock::GetCurrentDate() const
{
    return currentDate;
}