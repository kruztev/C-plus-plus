//
//  User.cpp
//  DrinkBook
//

#include "User.h"

const unsigned short MAX_AGE_VALUE = 97;
const unsigned short MAX_CASH_VALUE = 2000;
const unsigned short MAX_VODKAS_VALUE = 20;
const unsigned short MAX_WHISKEYS_VALUE = 20;

const char* musicDictionary[] = {"folk", "house", "rock"};

User::User() // This ctor is needed for the initialization of the dynamic array.
{
    name = "";
    age = 0;
    cash = 0;
    vodkas = 0;
    whiskeys = 0;
    music = ALL;
}

User::User(const String& nName, unsigned nAge, unsigned nCash, unsigned nVodkas, unsigned nWhiskeys, const char* music)
{
    setName(nName);
    setAge(nAge);
    setCash(nCash);
    setVodkas(nVodkas);
    setWhiskeys(nWhiskeys);
    setMusic(music);
}

const String& User::getName() const
{
    return name;
}

const unsigned User::getAge() const
{
    return age;
}

const unsigned User::getCash() const
{
    return cash;
}

const unsigned User::getVodkas() const
{
    return vodkas;
}

const unsigned User::getWhiskeys() const
{
    return whiskeys;
}

const MusicType User::getMusicType() const
{
    return music;
}

void User::setName(const String& nName) // Validation?
{
    name = nName;
}

void User::setAge(unsigned nAge)
{
    if (nAge > MAX_AGE_VALUE)
        throw "Invalid age value\n";
    age = nAge;
}

void User::setCash(unsigned nCash)
{
    if (nCash > MAX_CASH_VALUE)
        throw "Invalid cash value\n";
    cash = nCash;
}

void User::setVodkas(unsigned nVodkas)
{
    if (nVodkas > MAX_VODKAS_VALUE)
        throw "Alcohol dependence caught\n";
    vodkas = nVodkas;
}

void User::setWhiskeys(unsigned nWhiskeys)
{
    if (nWhiskeys > MAX_WHISKEYS_VALUE)
        throw "Alcohol dependence caught\n";
    whiskeys = nWhiskeys;
}

void User::setMusic(const char* genre)
{
    for (size_t i = 0; i < ALL; ++i)
    {
        if (!strcasecmp(musicDictionary[i], genre))
        {
            music = (MusicType)i;
            return;
        }
    }
    music = ALL;
}
