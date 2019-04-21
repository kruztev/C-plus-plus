//
//  Date.cpp
//  OOP Practices
//


#include <iostream>
#include <cmath>
#include "Date.h"

const unsigned short DEFAULT_DAY = 1;
const unsigned short DEFAULT_MONTH = 1;
const unsigned short DEFAULT_YEAR = 2000;
const unsigned short DAYS_COUNT = 31;
const unsigned short MONTHS_COUNT = 12;
const unsigned short DAYS_COUNT_FEB = 28;
const unsigned short JANUARY = 1;
const unsigned short FEBRUARY = 2;
const unsigned short MARCH = 3;
const unsigned short APRIL = 4;
const unsigned short JUNE = 6;
const unsigned short SEPTEMBER = 9;
const unsigned short NOVEMBER = 11;
const unsigned short DECEMBER = 12;
const unsigned short CHRSITMAS_DAY = 25;

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
            if (isLeap())
                handleDayAddition(newValue, DAYS_COUNT_FEB + 1);
            else
                handleDayAddition(newValue, DAYS_COUNT);
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

bool Date::isLaterThan(const Date& rhs) const
{
    if (year > rhs.year)
        return true;
    else if (year == rhs.year)
    {
        if (month > rhs.month)
            return true;
        else if (month == rhs.month)
        {
            if (day > rhs.day)
                return true;
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

unsigned int Date::daysToChristmas() const
{
    unsigned int daysLeft = 0;
    Date temp = *this;
    while (temp.month != DECEMBER)
    {
        temp.addDays(1);
        daysLeft++;
    }
    while (temp.day < CHRSITMAS_DAY)
    {
        temp.addDays(1);
        daysLeft++;
    }
    return daysLeft;
}

void Date::subtractDays(unsigned int countOfDays)
{
    for (int i = countOfDays; i > 0; --i)
    {
        unsigned int newValue = day - 1;
        if (month == APRIL || month == JUNE || month == SEPTEMBER || month == NOVEMBER)
        {
            handleDayAddition(newValue, DAYS_COUNT - 1);
        }
        else
        {
            handleDayAddition(newValue, DAYS_COUNT);
        }
    }
}

void Date::handleDaySubtraction(unsigned int newValue, unsigned short daysInMonth)
{
    if (newValue == 0)
    {
        if (month == MARCH && isLeap())
        {
            day = DAYS_COUNT_FEB + 1;
            month--;
        }
        else if (month == MARCH && !isLeap())
        {
            day = DAYS_COUNT_FEB;
            month--;
        }
        else
        {
            day = daysInMonth;
            if (month == 0)
            {
                month = DECEMBER;
                year--;
                return;
            }
            month--;
            return;
        }
    }
    day = newValue;
    return;
}

void Date::setDay(unsigned int day)
{
    if (month == FEBRUARY)
    {
       if (isLeap() && day > DAYS_COUNT_FEB + 1)
           this->day = DAYS_COUNT_FEB + 1;
        else if (day > DAYS_COUNT_FEB + 1)
            this->day = DAYS_COUNT_FEB;
        else
            this->day = day;
    }
    else if ((month == APRIL || month == JUNE || month == SEPTEMBER || month == NOVEMBER) && day > DAYS_COUNT - 1)
    {
        this->day = DAYS_COUNT - 1;
    }
    else if (day > DAYS_COUNT)
    {
        this->day = DAYS_COUNT;
    }
    else
    {
        this->day = day;
    }
    return;
}

void Date::setMonth(unsigned int month)
{
    if (month > MONTHS_COUNT)
        this->month = MONTHS_COUNT;
    else
        this->month = month;
    return;
}

void Date::setYear(unsigned int year)
{
    this->year = year;
}

unsigned int Date::getDay() const
{
    return day;
}

unsigned int Date::getMonth() const
{
    return month;
}

unsigned int Date::getYear() const
{
    return year;
}

Date getDifference(const Date& date1, const Date& date2)
{
    Date newDate;
    int newDay = date1.getDay() - date2.getDay();
    int newMonth = date1.getMonth() - date2.getMonth();
    int newYear = date1.getYear() - date2.getYear();
    newDate.setDay(std::abs(newDay));
    newDate.setMonth(std::abs(newMonth));
    newDate.setYear(std::abs(newYear));
    return newDate;
}
