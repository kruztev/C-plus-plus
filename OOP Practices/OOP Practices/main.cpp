//
//  main.cpp
//  OOP Practices
//

#include <iostream>
#include <fstream>
#include "Duelist.h"

int main()
{
    Deck d;//40 cards "Token" ATK: 0 DEF: 0
    // 4-th card in the deck becomes "Blue-eyes white dragon" with
    //ATK: 3000 DEF: 2500
    d.changeCard(4, "Blue-eyes white dragon", 3000, 2500);
    // 5-th card becomes the magic card "Monster reborn"
    d.changeCard(5, "Monster reborn");
    d.getMagicCardsCount(); //1
    d.getMonsterCardsCount(); //39
    d.saveToFile("MyDeck.bat"); //Saves the deck in to a file
    Deck d2("MyDeck.bat"); //Loads the deck from the file
    
    Duelist d3("Sasho");
    d3.saveToFile("MyFile.bat");
    Duelist duelist("Angel", "MyFile.bat");
    
    return 0;
}
