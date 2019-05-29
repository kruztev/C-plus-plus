//
//  Automaton.cpp
//  Nondeterministic Finite Automaton
//

#include "Automaton.h"

const unsigned short STARTING_VERTEX = 0;

Automaton& Automaton::unionOf2(const Automaton& automaton2) const
{
    Automaton* result = nullptr;
    try {
        result = new Automaton(*this);
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Bad alloc caught: " << ba.what() << '\n';
        throw;
    }
    result->copyTransitionsForUnion(*this, automaton2);
    
    for (unsigned i = 0; i < automaton2.finalStates.getSize(); ++i)
    {
        if (automaton2.finalStates[i] == STARTING_VERTEX)
        {
            result->finalStates.addElement(automaton2.finalStates[i]);
            continue;
        }
        // Calculate the new index in result of the vertex of the transition.
        unsigned newVertexIndex = this->automaton.getSize() + automaton2.finalStates[i] - 1;
        result->finalStates.addElement(newVertexIndex);
    }
    
    return *result;
}

void Automaton::addTransition(unsigned int fromVertex, unsigned int toVertex, char letter)
{
    Transition newTransition(toVertex, letter);
    automaton[fromVertex].addElement(newTransition);
}

void Automaton::copyTransitionsForUnion(const Automaton& automaton1, const Automaton& automaton2)
{
    // Copy the transitions from the starting vertex of automaton2 to the starting vertex of result (the new automata).
    for (unsigned int i = 0; i < automaton2.automaton[STARTING_VERTEX].getSize(); ++i)
    {
        this->addTransition(STARTING_VERTEX, this->automaton.getSize(), automaton2.automaton[STARTING_VERTEX][i].getLetter());
    }
    
    // Copy all other transitions of automaton2 to *this (result).
    for (unsigned int i = 1; i < automaton2.automaton.getSize(); ++i)
    {
        for (unsigned int j = 0; j < automaton2.automaton[i].getSize(); ++j)
        {
            if (automaton2.automaton[i][j].getToVertex() == STARTING_VERTEX)
            {
                this->addTransition(this->automaton.getSize(), STARTING_VERTEX, automaton2.automaton[i][j].getLetter());
            }
            else
            {
                // Calculate the new index in *this (result) of the vertex of the transition.
                unsigned newVertexIndex = automaton1.automaton.getSize() + automaton2.automaton[i][j].getToVertex() - 1;
                this->addTransition(this->automaton.getSize(), newVertexIndex, automaton2.automaton[i][j].getLetter());
            }
        }
    }
}

Automaton& Automaton::concatenationOf2(const Automaton& automaton2) const
{
    Automaton* result = nullptr;
    try {
        result = new Automaton(*this);
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Bad alloc caught: " << ba.what() << '\n';
        throw;
    }
    result->copyTransitionsForConcatenation(*this, automaton2);
    result->finalStates = automaton2.finalStates;
    result->determine();
    return *result;
}

void Automaton::copyTransitionsForConcatenation(const Automaton& automaton1, const Automaton& automaton2)
{
    // Add the transitions of the starting vertex of automaton2 to the final vertices of automaton1; automaton1.automaton.getSize() is the index of the starting vertex of automaton2.
    for (unsigned i = 0; i < automaton1.finalStates.getSize(); ++i)
    {
        for (unsigned j = 0; j < automaton2.automaton[STARTING_VERTEX].getSize(); ++j)
        {
            addTransition(automaton1.finalStates[i], automaton1.automaton.getSize(), automaton2.automaton[STARTING_VERTEX][j].getLetter());
        }
    }
    
    // Copy all other transitions of automaton2 to *this (result).
    for (unsigned int i = 1; i < automaton2.automaton.getSize(); ++i)
    {
        for (unsigned int j = 0; j < automaton2.automaton[i].getSize(); ++j)
        {
            if (automaton2.automaton[i][j].getToVertex() == STARTING_VERTEX)
            {
                for (unsigned k = 0; k < automaton1.finalStates.getSize(); ++k)
                {
                    // Copy transitions from vertices of automaton2 to the starting vertex of automaton2. The starting vertices in the new automaton are the final states of automaton1.
                    this->addTransition(this->automaton.getSize(), automaton1.finalStates[k], automaton2.automaton[i][j].getLetter());
                }
            }
            else
            {
                // Calculate the new index in *this (result) of the vertex of the transition.
                unsigned newVertexIndex = automaton1.automaton.getSize() + automaton2.automaton[i][j].getToVertex() - 1;
                this->addTransition(this->automaton.getSize(), newVertexIndex, automaton2.automaton[i][j].getLetter());
            }
        }
    }
    
    
}

void Automaton::determine()
{
    
}

Automaton& Automaton::kleeneStar() const
{
    Automaton* result = nullptr;
    try {
        result = new Automaton(*this);
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Bad alloc caught: " << ba.what() << '\n';
        throw;
    }
    // Copy transitions to the new automaton and incrementing vertex indexes by one because a new starting vertex will be added.
    for (unsigned i = 0; i < this->automaton.getSize(); ++i)
    {
        for (unsigned j = 0; j < this->automaton[i].getSize(); ++j)
        {
            result->addTransition(i+1, this->automaton[i][j].getToVertex() + 1, this->automaton[i][j].getLetter());
        }
    }
    // Copy transitions from the original starting vertex to the new starting vertex.
    for (unsigned i = 0; i < this->automaton[STARTING_VERTEX].getSize(); ++i)
    {
        result->addTransition(STARTING_VERTEX, this->automaton[STARTING_VERTEX][i].getToVertex() + 1, this->automaton[STARTING_VERTEX][i].getLetter());
    }
    // Add transitions from all final states to all post-start vertices
    for (unsigned i = 0; i < this->finalStates.getSize(); ++i)
    {
        result->addTransition(this->finalStates[i], this->automaton[STARTING_VERTEX][i].getToVertex() + 1, this->automaton[STARTING_VERTEX][i].getLetter());
    }
    result->finalStates = this->finalStates;
    result->finalStates.addElement(STARTING_VERTEX);
    return *result;
}
