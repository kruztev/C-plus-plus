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

const MusicType Club::getGenre() const
{
    return genre;
}

FolkClub::FolkClub(const char* name, unsigned vodkaPrice, unsigned whiskeyPrice, const char* artist)
: Club(name)
{
    setVodkaPrice(vodkaPrice);
    setWhiskeyPrice(whiskeyPrice);
    setArtist(artist);
    size = 0;
    genre = FOLK;
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
    genre = HOUSE;
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
    size = 0;
    genre = ROCK;
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
