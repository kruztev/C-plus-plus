//
//  Duelist.cpp
//  OOP Practices
//

#include <iostream>
#include <fstream>
#include "Duelist.h"

Duelist::Duelist(const char* name)
{
    try {
       this->name = new char[strlen(name)+1];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Cannot allocate memory for a new name\n";
        throw;
    }
    strcpy(this->name, name);
}

Duelist::Duelist(const Duelist& rhs)
{
    copy(rhs);
}

Duelist& Duelist::operator=(const Duelist& rhs)
{
    if (this != &rhs)
    {
        free();
        copy(rhs);
    }
    return *this;
}

Duelist::~Duelist()
{
    free();
}

void Duelist::copy(const Duelist& rhs)
{
    try {
        name = new char[strlen(rhs.name)+1];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Cannot allocate memory for a new name\n";
        throw;
    }
    strcpy(name, rhs.name);
    deck = rhs.deck;
}

void Duelist::free()
{
    delete[] name;
}

void Duelist::changeCard(size_t index, const char * name, unsigned int attackPoints, unsigned int defencePoints)
{
    deck.changeCard(index, name, attackPoints, defencePoints);
    return;
}

unsigned short Duelist::getMagicCardsCount() const
{
    return deck.getMagicCardsCount();
}

unsigned short Duelist::getMonsterCardsCount() const
{
    return deck.getMonsterCardsCount();
}

void Duelist::saveToFile(const char* fileName) const
{
    std::ofstream stream(fileName, std::ios::binary);
    if(!stream)
    {
        std::cerr << "Cannot open file for writing\n";
        return;
    }
    stream.write((const char*)this, sizeof(Duelist));
    stream.close();
    return;
}
