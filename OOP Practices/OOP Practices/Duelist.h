//
//  Duelist.h
//  OOP Practices
//

#ifndef Duelist_h
#define Duelist_h
#include "Deck.h"

class Duelist
{
public:
    Duelist(const char*);
    Duelist(const Duelist&);
    Duelist& operator=(const Duelist&);
    ~Duelist();
    Duelist(const char* duelistName, const char* fileName);
    
    void changeCard(size_t, const char[], unsigned int, unsigned int);
    unsigned short getMagicCardsCount() const;
    unsigned short getMonsterCardsCount() const;
    void saveToFile(const char*) const;
    
private: // Helper functions
    void copy(const Duelist&);
    void free();
    
private:
    char* name;
    Deck deck;
};

#endif
