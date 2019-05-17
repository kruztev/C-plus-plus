//
//  Deck.h
//  OOP Practices
//


#ifndef Deck_h
#define Deck_h
#include <istream>
#include "Card.h"

const unsigned short CARDS_COUNT = 40;

class Deck
{
public:
    Deck();
    Deck(const Deck&);
    Deck& operator=(const Deck&);
    ~Deck();
    Deck(const char[]);
    
    void changeCard(size_t, const char[], unsigned int = 0, unsigned int = 0);
    unsigned short getMagicCardsCount() const;
    unsigned short getMonsterCardsCount() const;
    void saveToFile(const char*) const;
    
private: // Helper functions
    void copy(const Deck&);
    void free();
    
private:
    Card* arr;
};


#endif
