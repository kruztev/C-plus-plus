//
//  Deck.cpp
//  OOP Practices
//

#include <iostream>
#include <fstream>
#include "Deck.h"

Deck::Deck()
{
    try {
        arr = new Card[CARDS_COUNT];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Cannot allocate memory for a new deck\n";
        throw;
    }
}

Deck::Deck(const Deck& rhs)
{
    copy(rhs);
}

Deck& Deck::operator=(const Deck& rhs)
{
    if (this != &rhs)
    {
        free();
        copy(rhs);
    }
    return *this;
}

Deck::~Deck()
{
    free();
}

Deck::Deck(const char fileName[])
{
    try {
        arr = new Card[CARDS_COUNT];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Cannot allocate memory for a new deck\n";
        throw;
    }
    
    std::ifstream streamIn(fileName, std::ios::binary);
    if (streamIn)
    {
        while (!streamIn.eof())
        {
            streamIn.read((char*)arr, sizeof(Deck));
            if (streamIn.eof())
                break;
        }
    }
    streamIn.close();
}

void Deck::changeCard(size_t index, const char name[], unsigned int attackPoints, unsigned int defencePoints)
{
    arr[index].setName(name);
    if (attackPoints == 0 && defencePoints == 0)
    {
        arr[index].setType(false); // Indicates that the card is not a monster.
        return;
    }
    arr[index].setAttackPoints(attackPoints);
    arr[index].setDefencePoints(defencePoints);
    return;
}

void Deck::copy(const Deck& rhs)
{
    try {
        arr = new Card[CARDS_COUNT];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Cannot allocate memory\n";
        throw;
    }
    for(size_t i = 0; i < CARDS_COUNT; ++i)
    {
        arr[i] = rhs.arr[i];
    }
}

void Deck::free()
{
    delete[] arr;
    arr = nullptr;
}

unsigned short Deck::getMagicCardsCount() const
{
    unsigned short countOfMagicCards = 0;
    for (size_t i = 0; i < CARDS_COUNT; ++i)
    {
        if (arr[i].getType() == 0)
        {
            countOfMagicCards++;
        }
    }
    return countOfMagicCards;
}

unsigned short Deck::getMonsterCardsCount() const
{
    return CARDS_COUNT - getMagicCardsCount();
}

void Deck::saveToFile(const char* fileName) const
{
    std::ofstream stream(fileName, std::ios::binary);
    if (!stream)
    {
        std::cerr << "Cannot open file\n";
        return;
    }
    
    stream.write((const char*)this, sizeof(Deck));
    stream.close();
    return;
}

