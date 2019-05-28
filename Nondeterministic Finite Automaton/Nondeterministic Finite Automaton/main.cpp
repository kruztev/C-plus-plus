//
//  main.cpp
//  Nondeterministic Finite Automaton
//

#include <iostream>
#include "myString.hpp"
#include "TemplateDynamicArray.hpp"

int main() {
    DynamicArray<String> arr;
    String a("Hello, world!");
    arr.addElement(a);
    
    return 0;
}
