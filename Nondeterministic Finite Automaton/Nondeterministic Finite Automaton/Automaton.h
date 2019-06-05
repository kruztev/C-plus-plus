//
//  Automaton.h
//  Nondeterministic Finite Automaton
//


#ifndef Automaton_h
#define Automaton_h
#include "TemplateDynamicArray.hpp"
#include "Transition.h"
#include "String.h"

const unsigned short STARTING_VERTEX = 0;

class Automaton
{
public:
    Automaton() = default;
//    Automaton(const String&); // Constructs automaton of a regex.
    Automaton(const Automaton&) = default;
    Automaton& operator=(const Automaton&) = default;
    ~Automaton() = default;
    friend std::ostream& operator<<(std::ostream&, const Automaton&);
    
    
    
public:
    Automaton& unionOf2(const Automaton&) const;
    Automaton concatenationOf2(const Automaton&) const;
    void kleeneStar();
    void determine();
//    void minimalize();
    void totalize();
    bool acceptWord(const String& string, unsigned stringPos = 0, unsigned startingVertex = STARTING_VERTEX) const;
    bool acceptEmptyWord() const;
//    const String& regexOfAnAutomaton() const; // Returns a regex of an automaton.
    void addFinalState(unsigned); // This function should be private, but because of demonstrational purposes is public.
    void addTransitionFromOutside(const DynamicArray<Transition> transitions);
    
private:
    void addTransition(unsigned fromVertex, unsigned toVertex, char letter);
    void copyTransitionsForUnion(const Automaton&, const Automaton&);
    void copyTransitionsForConcatenation(const Automaton&, const Automaton&);
    bool isFinal(unsigned state) const;
    bool transitionExist(unsigned fromVertex, unsigned toVertex, char letter) const;
    
private:
   DynamicArray<DynamicArray<Transition>>  automaton;
    DynamicArray<unsigned> finalStates;
};

#endif
