//
//  Clock.cpp
//  OOP Practices
//

#include <iostream>
#include "Clock.h"
#include <time.h>

const unsigned short DEFAULT_HOURS = 9;
const unsigned short DEFAULT_MINUTES = 24;
const unsigned short DEFAULT_SECONDS = 12;
const unsigned short MAX_HOURS_VALUE = 23;
const unsigned short MAX_MINUTES_VALUE = 60;
const unsigned short MAX_SECONDS_VALUE = 60;

Clock::Clock()
{
    syncTime();
}

Clock::Clock(const unsigned hours, const unsigned minutes, const unsigned seconds)
{
    setHours(hours);
    setMinutes(minutes);
    setSeconds(seconds);
}

Clock::Clock(const Clock& clock)
{
    *this = clock;
}

Clock& Clock::operator=(const Clock& clock)
{
    if(this != &clock)
    {
        this->hours = clock.hours;
        this->minutes = clock.minutes;
        this->seconds = clock.seconds;
    }
    return *this;
}

Clock Clock::operator+(const Clock& rhs)
{
    Clock newClock;
    
    newClock.seconds = rhs.seconds + this->seconds;
    if(newClock.seconds > MAX_SECONDS_VALUE)
    {
        newClock.minutes += 1;
        newClock.seconds = newClock.seconds % MAX_SECONDS_VALUE;
    }
    newClock.minutes = rhs.minutes + this->minutes;
    if(newClock.minutes > MAX_MINUTES_VALUE)
    {
        newClock.hours += 1;
        newClock.minutes = newClock.minutes % MAX_MINUTES_VALUE;
    }
    newClock.hours = rhs.hours + this->hours;
    if(newClock.hours > MAX_HOURS_VALUE)
    {
        newClock.hours = newClock.hours % MAX_HOURS_VALUE;
    }
    return newClock;
}

Clock::~Clock()
{}

void Clock::setHours(unsigned int hours)
{
    if(hours < 0 && hours > 24)
    {
        std::cerr << "Invalid input. Setting default hours.\n";
        this->hours = DEFAULT_HOURS;
        return;
    }
    this->hours = hours;
}

void Clock::setMinutes(unsigned int minutes)
{
    if(minutes < 0 && hours > 59)
    {
        std::cerr << "Invalid input. Setting default minutes.\n";
        this->hours = DEFAULT_MINUTES;
        return;
    }
    this->minutes = minutes;
}

void Clock::setSeconds(unsigned int seconds)
{
    if(seconds < 0 && seconds > 59)
    {
        std::cerr << "Invalid input. Setting default seconds.\n";
        this->hours = DEFAULT_SECONDS;
        return;
    }
    this->seconds = seconds;
}

void Clock::setClock(unsigned int hours, unsigned int minutes, unsigned int seconds)
{
    setHours(hours);
    setMinutes(minutes);
    setSeconds(seconds);
}

void Clock::print()
{
    if (hours < 10)
    {
        std::cout << 0 << hours << ':';
    }
    else
    {
        std::cout << hours << ':';
    }
    if (minutes < 10)
    {
        std:: cout << 0 << minutes << ':';
    }
    else
    {
        std::cout << minutes << ':';
    }
    if (seconds < 10)
    {
        std:: cout << 0 << seconds << '\n';
    }
    else
    {
        std::cout << seconds << '\n';
    }
}

void Clock::nextTick()
{
    if (seconds == 59)
    {
        if (minutes == 59)
        {
           if (hours == 23)
           {
               hours = 0;
               minutes = 0;
               seconds = 0;
               return;
           }
            minutes = 0;
            seconds = 0;
            hours++;
            return;
        }
        seconds = 0;
        minutes++;
        return;
    }
    seconds++;
    return;
}

void Clock::syncTime()
{
    time_t time;
    struct tm* timeinfo;
    timeinfo = localtime(&time);
    seconds = timeinfo->tm_sec;
    minutes = timeinfo->tm_min;
    hours = timeinfo->tm_hour;
}
