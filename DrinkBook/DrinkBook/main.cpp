//
//  main.cpp
//  DrinkBook
//

#include <iostream>
#include "Clubs.h"

int main() {
    //Example
    Clubs d;
    
    try {
        d.addRockClub("Road 66",40,20);//False (the whiskey is too cheap)
    } catch (const char* text) {
        std::cout << text;
        return -1;
    }
    
    d.addRockClub("Road 66",40,40); // Much better
    d.addHouseClub("Yalta",50,50,2); // 50 for whiskey,50 for vodka and 2 DJs this night.
    User u("Ivan",18,180,2,2,"Rock"); // Name: Ivan, Age: 18, Cash: 180, Vodkas:2, Whiskeys: 2, Music: House
    std::cout << d.addToClub(u,"Yalta") << '\n'; // not enough cash for 2 vodkas and 2 whiskeys
    std::cout << d.addToClub(u,"Road 66") << '\n'; // True
    d.removeFromClub("Poli","Yalta"); // False. No Poli in 33 tonight
    d.removeFromClub("Ivan","Road 66"); // True

    return 0;
}
