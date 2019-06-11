//
//  Club.cpp
//  DrinkBook
//

#include "Club.h"

Club::Club(const char* nName)
{
    setName(nName);
}

const String& Club::getName() const
{
    return name;
}

const unsigned Club::getVodkaPrice() const
{
    return vodkaPrice;
}

const unsigned Club::getWhiskeyPrice() const
{
    return whiskeyPrice;
}

void Club::setName(const char* nName)
{
    name = nName;
}

void Club::removeUser(const char *name)
{
    String nameToString(name);
    for (size_t i = 0; i < users.getSize(); ++i)
    {
        if (users[i].getName() == nameToString)
        {
            users.removeAt(i);
            return;
        }
    }
    std::cout << "There is no " << name << " in this club tonight\n";
}

FolkClub::FolkClub(const char* name, unsigned vodkaPrice, unsigned whiskeyPrice, const char* artist)
: Club(name)
{
    setVodkaPrice(vodkaPrice);
    setWhiskeyPrice(whiskeyPrice);
    setArtist(artist);
    capacity = FOLK_CAPACITY;
}

void FolkClub::setVodkaPrice(unsigned nVodkaPrice)
{
    if (nVodkaPrice < VODKA_LOW_LIMIT_FOLK)
        throw "Too cheap vodka\n";
    vodkaPrice = nVodkaPrice;
}

void FolkClub::setWhiskeyPrice(unsigned nWhiskeyPrice)
{
    if (nWhiskeyPrice < WHISKEY_LOW_LIMIT_FOLK)
        throw "Too cheap whiskey\n";
    whiskeyPrice = nWhiskeyPrice;
}

bool FolkClub::addUser(User& u)
{
    if (u.getMusicType() == ROCK)
    {
        std::cerr << "User doesn't like club's music\n";
        return false;
    }
    if (users.getSize() == capacity)
    {
        std::cerr << "The club is full\n";
        return false;
    }
    if (u.getCash() < (u.getVodkas() * vodkaPrice + u.getWhiskeys() * whiskeyPrice))
    {
        std::cerr << "Not enough cash for drinks\n";
        return false;
    }
    if (u.getAge() < MIN_AGE)
    {
        u.setCash(u.getCash() - CHARGE_FORGOTTEN_ID);
    }
    users.addElement(u);
    return true;
}

void FolkClub::setArtist(const char* nArtist)
{
    artist = nArtist;
}

const String& FolkClub::getArtist() const
{
    return artist;
}

HouseClub::HouseClub(const char* name, unsigned vodkaPrice, unsigned whiskeyPrice, unsigned countOfDJs)
: Club(name)
{
    setVodkaPrice(vodkaPrice);
    setWhiskeyPrice(whiskeyPrice);
    setDjs(countOfDJs);
    //genre = HOUSE;
}

void HouseClub::setVodkaPrice(unsigned nVodkaPrice)
{
    if (nVodkaPrice < VODKA_LOW_LIMIT_HOUSE)
        throw "Too cheap vodka\n";
    vodkaPrice = nVodkaPrice;
}

void HouseClub::setWhiskeyPrice(unsigned nWhiskeyPrice)
{
    if (nWhiskeyPrice < WHISKEY_LOW_LIMIT_HOUSE)
        throw "Too cheap whiskey\n";
    whiskeyPrice = nWhiskeyPrice;
}

bool HouseClub::addUser(User& u)
{
    if (u.getMusicType() == FOLK)
    {
        std::cerr << "User doesn't like club's music\n";
        return false;
    }
    if (u.getCash() < (u.getVodkas()*vodkaPrice + u.getWhiskeys()*whiskeyPrice))
    {
        std::cerr << "Not enough cash for drinks\n";
        return false;
    }
    if (u.getAge() < MIN_AGE)
    {
        std::cerr << "User's too young\n";
        return false;
    }
    users.addElement(u);
    return true;
}

void HouseClub::setDjs(unsigned countOfDjs)
{
    djs = countOfDjs;
}

unsigned HouseClub::getDjs() const
{
    return djs;
}

RockClub::RockClub(const char* name, unsigned vodkaPrice, unsigned whiskeyPrice)
: Club(name)
{
    setVodkaPrice(vodkaPrice);
    setWhiskeyPrice(whiskeyPrice);
    capacity = ROCK_CAPACITY;
}

void RockClub::setVodkaPrice(unsigned nVodkaPrice)
{
    if (nVodkaPrice < VODKA_LOW_LIMIT_ROCK)
        throw "Too cheap vodka\n";
    vodkaPrice = nVodkaPrice;
}

void RockClub::setWhiskeyPrice(unsigned nWhiskeyPrice)
{
    if (nWhiskeyPrice < WHISKEY_LOW_LIMIT_ROCK)
        throw "Too cheap whiskey\n";
    whiskeyPrice = nWhiskeyPrice;
}

bool RockClub::addUser(User& u)
{
    if (u.getMusicType() == HOUSE)
    {
        std::cerr << "User doesn't like club's music\n";
        return false;
    }
    if (users.getSize() == capacity)
    {
        std::cerr << "The club is full\n";
        return false;
    }
    if (u.getCash() < (u.getVodkas()*vodkaPrice + u.getWhiskeys()*whiskeyPrice))
    {
        std::cerr << "Not enough cash for drinks\n";
        return false;
    }
    if (u.getAge() < MIN_AGE)
    {
        std::cerr << "User's too young\n";
        return false;
    }
    users.addElement(u);
    return true;
}
