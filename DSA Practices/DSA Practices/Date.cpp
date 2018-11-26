//
//  Date.cpp
//  SDP Practs
//

#include "Date.hpp"
#include <iostream>



Date::Date(const unsigned day, const unsigned month, const unsigned year)
{
    if(!dateIsValid(day, month, year))
    {
        throw std::invalid_argument("Invalid argument.\n");
    }
    date[0] = day/10 + '0';
    date[1] = day%10 + '0';
    date[2] = '-';
    date[3] = month/10 + '0';
    date[4] = month%10 + '0';
    date[5] = '-';
    date[6] = year/1000 + '0';
    date[7] = (year/100)%10 + '0';
    date[8] = (year%100)/10 + '0';
    date[9] = year%10 + '0';
    date[10] = '\0';
}

bool Date::dateIsValid(const unsigned day, const unsigned month, const unsigned year) const
{
    if(day > 31 || (month > 12 || month < 1))
    {
        return 0;
    }
    if (day > 30 && (month == 2 || month == 4 || month == 6 || month == 9 || month == 11))
    {
        return 0;
    }
    if(year <= 1000)
    {
        return 0;
    }
    return 1;
}

const char* Date::getDate() const
{
    return this->date;
}
