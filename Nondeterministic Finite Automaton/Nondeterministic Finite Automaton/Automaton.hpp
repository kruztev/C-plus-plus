//
//  Automaton.hpp
//  Nondeterministic Finite Automaton
//


#ifndef Automaton_hpp
#define Automaton_hpp
#include "TemplateDynamicArray.hpp"
#include "Transition.hpp"


class Automaton
{
public:
    
private:
   DynamicArray<DynamicArray<Transition>>  automaton;
};

#endif
