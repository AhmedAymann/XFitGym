#include "ProgramClock.h"

ProgramClock::ProgramClock()
{
    currentDate = QDate::currentDate(); // start from a fixed date for testing
}

void ProgramClock::Tick()
{
    currentDate = currentDate.addDays(1);
}

QDate ProgramClock::GetCurrentDate() const
{
    return currentDate;
}