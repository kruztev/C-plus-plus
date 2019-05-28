//
//  Automaton.cpp
//  Nondeterministic Finite Automaton
//

#include "Automaton.h"

const unsigned short STARTING_VERTEX = 0;

Automaton& Automaton::unionOf2(const Automaton& automata1, const Automaton& automata2)
{
    Automaton* result = nullptr;
    try {
        result = new Automaton(automata1);
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Bad alloc caught: " << ba.what() << '\n';
        throw;
    }
    copyTransitions(automata1, automata2, result);
    
    for (unsigned i = 0; i < automata2.finalStates.getSize(); ++i)
    {
        if (automata2.finalStates[i] == STARTING_VERTEX)
        {
            result->finalStates.addElement(automata2.finalStates[i]);
            continue;
        }
        // Calculate the new index in result of the vertex of the transition.
        unsigned newVertexIndex = automata1.automaton.getSize() + automata2.finalStates[i] - 1;
        result->finalStates.addElement(newVertexIndex);
    }
    
    return *result;
}

void Automaton::addTransition(unsigned int fromVertex, unsigned int toVertex, char letter)
{
    Transition newTransition(toVertex, letter);
    automaton[fromVertex].addElement(newTransition);
}

void Automaton::copyTransitions(const Automaton& automata1, const Automaton& automata2, Automaton* result)
{
    // Copy the transitions from the starting vertex of automata2 to the starting vertex of result (the new automata).
    for (unsigned int i = 0; i < automata2.automaton[STARTING_VERTEX].getSize(); ++i)
    {
        result->addTransition(STARTING_VERTEX, result->automaton.getSize(), automata2.automaton[STARTING_VERTEX][i].letter);
    }
    
    // Copy all other transitions of automata2 to result.
    for (unsigned int i = 1; i < automata2.automaton.getSize(); ++i)
    {
        for (unsigned int j = 0; j < automata2.automaton[i].getSize(); ++j)
        {
            if (automata2.automaton[i][j].toVertex == STARTING_VERTEX)
            {
                Transition temp(STARTING_VERTEX, automata2.automaton[i][j].letter);
                result->automaton[result->automaton.getSize()].addElement(temp);
            }
            else
            {
                // Calculate the new index in result of the vertex of the transition.
                unsigned newVertexIndex = automata1.automaton.getSize() + automata2.automaton[i][j].toVertex - 1;
                Transition temp(newVertexIndex, automata2.automaton[i][j].letter);
                result->automaton[result->automaton.getSize()].addElement(temp);
            }
        }
    }
}
