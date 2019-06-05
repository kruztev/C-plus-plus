//
//  Transition.cpp
//  Nondeterministic Finite Automaton
//


#include "Transition.h"

Transition::Transition(unsigned toVertex, char letter)
{
    this->toVertex = toVertex;
    this->letter = letter;
}

unsigned Transition::getToVertex() const
{
    return toVertex;
}

char Transition::getLetter() const
{
    return letter;
}
