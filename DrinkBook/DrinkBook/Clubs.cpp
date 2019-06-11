//
//  Clubs.cpp
//  DrinkBook
//

#include "Clubs.h"

void Clubs::addFolkClub(const char *name, unsigned int vodkaPrice, unsigned int whiskeyPrice, const char *artist)
{
    Club* pToFolkClub = new FolkClub(name, vodkaPrice, whiskeyPrice, artist);
    array.addElement(pToFolkClub);
}

void Clubs::addRockClub(const char *name, unsigned int vodkaPrice, unsigned int whiskeyPrice)
{
    Club* pToRockClub = new RockClub(name, vodkaPrice, whiskeyPrice);
    array.addElement(pToRockClub);
}

void Clubs::addHouseClub(const char *name, unsigned int vodkaPrice, unsigned int whiskeyPrice, unsigned int countOfDjs)
{
    Club* pToHouseClub = new HouseClub(name, vodkaPrice, whiskeyPrice, countOfDjs);
    array.addElement(pToHouseClub);
}

void Clubs::removeClub(const char* name)
{
    String nameToString(name);
    for (size_t i = 0; i < array.getSize(); ++i)
    {
        if (array[i]->getName() == nameToString)
        {
            array.removeAt(i);
            return;
        }
    }
    std::cout << "There is no " << name << " club tonight\n";
}

bool Clubs::addToClub(User& user, const char* clubName)
{
    String nameToString(clubName);
    for (size_t i = 0; i < array.getSize(); ++i)
    {
        if (array[i]->getName() == nameToString)
        {
            return array[i]->addUser(user);
        }
    }
    return false;
}

void Clubs::removeFromClub(const char *name, const char *clubName)
{
    String nameToString(clubName);
    for (size_t i = 0; i < array.getSize(); ++i)
    {
        if (array[i]->getName() == nameToString)
        {
            array[i]->removeUser(name);
            return;
        }
    }
}
