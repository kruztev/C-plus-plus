//
//  Clubs.h
//  DrinkBook
//


#ifndef Clubs_h
#define Clubs_h
#include "Club.h"
#include "TemplateDynamicArray.hpp"

class Clubs
{
public:
    Clubs() = default;
    Clubs(const Clubs&) = default;
    Clubs& operator=(const Clubs&) = default;
    ~Clubs() = default;
    
    void addFolkClub(const char* name, unsigned vodkaPrice, unsigned whiskeyPrice, const char* artist);
    void addHouseClub(const char* name, unsigned vodkaPrice, unsigned whiskeyPrice, unsigned countOfDjs);
    void addRockClub(const char* name, unsigned vodkaPrice, unsigned whiskeyPrice);
    void removeClub(const char* name);
    bool addToClub(User& user, const char*); // Non-const type User used, because when added to folk club, it's cash must be accessible.
    void removeFromClub(const char* name, const char* clubName);
    
private:
    DynamicArray<Club*> array;
};

#endif
