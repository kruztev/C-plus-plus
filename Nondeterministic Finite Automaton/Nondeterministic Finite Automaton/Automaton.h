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
    Automaton& unionOf2(const Automaton&) const;
    Automaton& concatenationOf2(const Automaton&) const;
    void determine();
    Automaton& kleeneStar() const;
    
private:
    void addTransition(unsigned fromVertex, unsigned toVertex, char letter);
    void copyTransitionsForUnion(const Automaton&, const Automaton&);
    void copyTransitionsForConcatenation(const Automaton&, const Automaton&);
    
private:
   DynamicArray<DynamicArray<Transition>>  automaton;
    DynamicArray<unsigned> finalStates;
};

#endif
