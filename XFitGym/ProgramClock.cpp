#include "ProgramClock.h"

ProgramClock::ProgramClock()
{
    currentDate = QDate(2025, 1, 1);
    //currentDate = QDate::currentDate();   if you want to start the program from todays date 
}

void ProgramClock::Tick()
{
    currentDate = currentDate.addDays(1);
}



QDate ProgramClock::GetCurrentDate() const
{
    return currentDate;
}