//
//  Club.h
//  DrinkBook
//

#ifndef Club_h
#define Club_h
#include "String.h"
#include "User.h"

const unsigned short FOLK_CAPACITY = 70;
const unsigned short ROCK_CAPACITY = 30;
const unsigned short VODKA_LOW_LIMIT_FOLK = 20;
const unsigned short WHISKEY_LOW_LIMIT_FOLK = 35;
const unsigned short VODKA_LOW_LIMIT_HOUSE = 30;
const unsigned short WHISKEY_LOW_LIMIT_HOUSE = 40;
const unsigned short VODKA_LOW_LIMIT_ROCK = 40;
const unsigned short WHISKEY_LOW_LIMIT_ROCK = 30;


class Club
{
public:
    Club(const char*);
    Club(const Club&) = default;
    Club& operator=(const Club&) = default;
    virtual ~Club() = default;
    
    void setName(const char*);
    virtual void setVodkaPrice(unsigned) = 0;
    virtual void setWhiskeyPrice(unsigned) = 0;
    
    const String& getName() const;
    const unsigned getVodkaPrice() const;
    const unsigned getWhiskeyPrice() const;
    const MusicType getGenre() const;
    
protected:
    unsigned vodkaPrice;
    unsigned whiskeyPrice;
    MusicType genre;
    
private:
    String name;
};

class FolkClub : public Club
{
public:
    FolkClub(const char* name, unsigned vodkaPrice, unsigned whiskeyPrice, const char* artist);
    FolkClub(const FolkClub&) = default;
    FolkClub& operator=(const FolkClub&) = default;
    ~FolkClub() = default;
    
    void setVodkaPrice(unsigned);
    void setWhiskeyPrice(unsigned);
    void setArtist(const char*);
    const String& getArtist() const;
    
private:
    unsigned capacity;
    unsigned size;
    String artist;
};

class HouseClub : public Club
{
public:
    HouseClub(const char* name, unsigned vodkaPrice, unsigned whiskeyPrice, unsigned countOfDJs);
    
    void setVodkaPrice(unsigned);
    void setWhiskeyPrice(unsigned);
    void setDjs(unsigned);
    unsigned getDjs() const;
    
private:
    unsigned djs; // count of DJs
};

class RockClub : public Club
{
public:
    RockClub(const char* name, unsigned vodkaPrice, unsigned whiskeyPrice);
    RockClub(const RockClub&) = default;
    RockClub& operator=(const RockClub&) = default;
    ~RockClub() = default;
    
    void setVodkaPrice(unsigned);
    void setWhiskeyPrice(unsigned);
    
    
private:
    unsigned capacity;
    unsigned size;
};
#endif
