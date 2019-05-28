//
//  Automaton.h
//  Nondeterministic Finite Automaton
//


#ifndef Automaton_h
#define Automaton_h
#include "TemplateDynamicArray.hpp"
#include "Transition.hpp"


class Automaton
{
public:
    Automaton();
    Automaton& unionOf2(const Automaton&, const Automaton&);
    
private:
    void addTransition(unsigned fromVertex, unsigned toVertex, char letter);
    void copyTransitions(const Automaton&, const Automaton&, Automaton*);
    
private:
   DynamicArray<DynamicArray<Transition>>  automaton;
    DynamicArray<unsigned> finalStates;
};

#endif
