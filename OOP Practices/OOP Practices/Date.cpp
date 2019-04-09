//
//  Date.cpp
//  OOP Practices
//

#include "Date.h"

const unsigned short DEFAULT_DAY = 1;
const unsigned short DEFAULT_MONTH = 1;
const unsigned short DEFAULT_YEAR = 2000;
const unsigned short DAYS_COUNT = 31;
const unsigned short MONTHS_COUNT = 12;
const unsigned short DAYS_COUNT_FEB = 28;
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
    unsigned int newDaysValue = day + countOfDays;
    if (month == FEBRUARY)
    {
        if (isLeap() && newDaysValue > DAYS_COUNT_FEB + 1)
        {
            if (day + newDaysValue > DAYS_COUNT_FEB + 1)
            {
                unsigned int temp = calculateMonths(newDaysValue, DAYS_COUNT_FEB + 1);
                day = newDaysValue % DAYS_COUNT_FEB + 1;
                if (month + temp > MONTHS_COUNT)
                {
                   // ???
                }
            }
            else
            {
                day += newDaysValue;
            }
            
        }
    }
}

unsigned int Date::calculateMonths(unsigned int days, unsigned int countOfDaysInMonth) const
{
    unsigned int monthsToAdd = 0;
    while (days != 0)
    {
        days /= countOfDaysInMonth;
        monthsToAdd++;
    }
    return monthsToAdd;
}

