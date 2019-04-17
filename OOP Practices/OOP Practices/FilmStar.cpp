//
//  FilmStar.cpp
//

#include <iostream>
#include "FilmStar.h"

void FilmStar::setId(const unsigned long long Id)
{
    this->Id = Id;
    return;
}

void FilmStar::setFirstName(const char name[])
{
    strcpy(FirstName, name);
    return;
}

void FilmStar::setLastName(const char name[])
{
    strcpy(LastName, name);
    return;
}

void FilmStar::setFilms(unsigned long long Films)
{
    this->Films = Films;
    return;
}

unsigned long long FilmStar::getId() const
{
    return Id;
}

const char* FilmStar::getFirstName() const
{
    return FirstName;
}

const char* FilmStar::getLastName() const
{
    return LastName;
}

unsigned long long FilmStar::getFilms() const
{
    return Films;
}
