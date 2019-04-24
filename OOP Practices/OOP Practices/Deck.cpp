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
    std::ifstream streamIn(fileName);
    if (!streamIn)
    {
        Deck();
    }
    else
    {
        Deck();
        size_t count = 0;
        while (!streamIn.eof())
        {
            streamIn.read((char*)&arr[count], sizeof(Card));
            if (streamIn.eof())
                break;
            count++;
        }
    }
}

void Deck::changeCard(size_t index, const char name[], unsigned int attackPoints = 0, unsigned int defencePoints = 0)
{
    if (attackPoints == 0 && defencePoints == 0)
    {
        arr[index].setType(false);
        arr[index].setName(name);
        return;
    }
    arr[index].setName(name);
    arr[index].setAttackPoints(attackPoints);
    arr[index].setDefencePoints(defencePoints);
    return;
}

void Deck::copy(const Deck& rhs)
{
    Card* temp = nullptr;
    try {
        temp = new Card[CARDS_COUNT];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Cannot allocate memory\n";
        throw;
    }
    for(size_t i = 0; i < CARDS_COUNT; ++i)
    {
        temp[i] = arr[i];
    }
    free();
    arr = temp;
    return;
}

void Deck::free()
{
    delete[] arr;
}
