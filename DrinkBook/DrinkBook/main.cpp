//
//  main.cpp
//  DrinkBook
//

#include <iostream>
#include "Club.h"

int main() {
    try {
        FolkClub a("33", 10, 40, "Galena");
    } catch (const char* a) {
        std::cout << a;
    }
    
    return 0;
}
