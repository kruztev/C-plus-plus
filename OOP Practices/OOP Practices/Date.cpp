//
//  Date.cpp
//  OOP Practices
//

#include <iostream>
#include "Date.h"

const unsigned short DEFAULT_DAY = 1;
const unsigned short DEFAULT_MONTH = 1;
const unsigned short DEFAULT_YEAR = 2000;
const unsigned short DAYS_COUNT = 31;
const unsigned short MONTHS_COUNT = 12;
const unsigned short DAYS_COUNT_FEB = 28;
const unsigned short JANUARY = 1;
const unsigned short FEBRUARY = 2;
const unsigned short APRIL = 4;
const unsigned short JUNE = 6;
const unsigned short SEPTEMBER = 9;
const unsigned short NOVEMBER = 11;

Date::Date() : day(DEFAULT_DAY), month(DEFAULT_MONTH),
year(DEFAULT_YEAR)
{}

Date::Date(unsigned int day, unsigned int month, unsigned int year)
{
    if (isValidDate(day, month, year))
    {
        this->day = day;
        this->month = month;
        this->year = year;
    }
    else
    {
        this->day = DEFAULT_DAY;
        this->month = DEFAULT_MONTH;
        this->year = DEFAULT_YEAR;
    }
}

bool Date::isLeap() const
{
    if (this->year % 4 == 0 && this->year % 100 != 0)
    {
        return true;
    }
    return false;
}

bool Date::isValidDate(unsigned int day, unsigned int month, unsigned int year) const
{
    if (day < 0 || day > DAYS_COUNT)
    {
        return false;
    }
    
    if (month == FEBRUARY)
    {
        if (day == DAYS_COUNT_FEB + 1) // Checking the leap year case.
        {
            return (year % 4 == 0 && year % 100 != 0);
        }
        return day <= DAYS_COUNT_FEB;
    }
    
    if (day == DAYS_COUNT)
    {
        if (month == APRIL || month == JUNE || month == SEPTEMBER || month == NOVEMBER)
        {
            return false;
        }
    }
    return true;
    
}

void Date::addDays(unsigned int countOfDays)
{
    for (int i = countOfDays; i > 0; --i)
    {
        unsigned int newValue = day + 1;
        if (month == FEBRUARY)
        {
            handleFebruary(newValue);
        }
        else if (month == APRIL || month == JUNE || month == SEPTEMBER || month == NOVEMBER)
        {
            handleDayAddition(newValue, DAYS_COUNT - 1);
        }
        else
        {
            handleDayAddition(newValue, DAYS_COUNT);
        }
    }
}

void Date::handleFebruary(unsigned int newValue) // newValue = day + 1
{
    if (isLeap() && newValue > DAYS_COUNT_FEB + 1)
    {
        if (month == MONTHS_COUNT)
        {
            day = newValue % DAYS_COUNT_FEB + 1;
            year++;
            month = JANUARY;
            return;
        }
        
        day = newValue % DAYS_COUNT_FEB + 1;
        month++;
    }
    else if (newValue > DAYS_COUNT_FEB)
    {
        if (month == MONTHS_COUNT)
        {
            day = newValue % DAYS_COUNT_FEB;
            year++;
            month = JANUARY;
            return;
        }
        
        day = newValue % DAYS_COUNT_FEB;
        month++;
    }
    else
    {
        day = newValue;
    }
    return;
}

void Date::handleDayAddition(unsigned int newValue, unsigned short daysInMonth)
{
    if (newValue > daysInMonth)
    {
        day = newValue % daysInMonth;
        if (month == MONTHS_COUNT)
        {
            month = JANUARY;
            year++;
            return;
        }
        month++;
        return;
    }
    day = newValue;
    return;
}
