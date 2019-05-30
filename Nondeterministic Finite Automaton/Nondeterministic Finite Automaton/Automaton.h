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
    Automaton& kleeneStar() const;
    void determine();
    void totalize();
    
    
private:
    void addTransition(unsigned fromVertex, unsigned toVertex, char letter);
    void copyTransitionsForUnion(const Automaton&, const Automaton&);
    void copyTransitionsForConcatenation(const Automaton&, const Automaton&);
    void copyTransitionsForDetermination(const DynamicArray<DynamicArray<unsigned int>>& verticesThatWillBeCombined, Automaton& result, unsigned newVertexIndex, char letter);
    void checkForFinalDestinations(const Automaton& originalAutomaton, const DynamicArray<DynamicArray<unsigned int>>& verticesThatWillBeCombined, unsigned currentVertex);
    
private:
   DynamicArray<DynamicArray<Transition>>  automaton;
    DynamicArray<unsigned> finalStates;
};

#endif
