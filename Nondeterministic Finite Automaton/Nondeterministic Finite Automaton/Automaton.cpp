//
//  Automaton.cpp
//  Nondeterministic Finite Automaton
//

#include "Automaton.h"

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
    
    // Copy final destinations to the new automaton.
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
    // Copy the transitions from the starting vertex of automaton2 to the starting vertex of result (this).
    for (unsigned int i = 0; i < automaton2.automaton[STARTING_VERTEX].getSize(); ++i)
    {
        this->addTransition(STARTING_VERTEX, this->automaton.getSize(), automaton2.automaton[STARTING_VERTEX][i].getLetter());
    }
    std::cout << *this << '\n';
    
    // Copy all other transitions of automaton2 to result (this).
    for (unsigned int i = 1; i < automaton2.automaton.getSize(); ++i)
    {
        DynamicArray<Transition> tempArr;
        for (unsigned int j = 0; j < automaton2.automaton[i].getSize(); ++j)
        {
            if (automaton2.automaton[i][j].getToVertex() == STARTING_VERTEX)
            {
                Transition tempTrans(STARTING_VERTEX, automaton2.automaton[i][j].getLetter());
                tempArr.addElement(tempTrans);
            }
            else
            {
                // Calculate the new index in result (this) of the vertex of the transition.
                unsigned newVertexIndex = automaton1.automaton.getSize() + automaton2.automaton[i][j].getToVertex() - 1;
                Transition tempTrans(newVertexIndex, automaton2.automaton[i][j].getLetter());
                tempArr.addElement(tempTrans);
            }
        }
        std::cout << *this << '\n';
        this->automaton.addElement(tempArr);
    }
}

Automaton Automaton::concatenationOf2(const Automaton& automaton2) const
{
    Automaton result(*this);
//    try {
//        result = new Automaton(*this);
//    } catch (const std::bad_alloc& ba) {
//        std::cerr << "Bad alloc caught: " << ba.what() << '\n';
//        throw;
//    }
    result.copyTransitionsForConcatenation(*this, automaton2);
    result.finalStates = automaton2.finalStates;
    result.determine();
    return result;
}

void Automaton::copyTransitionsForConcatenation(const Automaton& automaton1, const Automaton& automaton2)
{
    // Add the transitions from the final vertices of automaton1 to the starting vertices of automaton2; automaton1.automaton.getSize() is the index of the starting vertex of automaton2.
    for (unsigned i = 0; i < automaton1.finalStates.getSize(); ++i)
    {
        DynamicArray<Transition> tempArr;
        for (unsigned j = 0; j < automaton2.automaton[STARTING_VERTEX].getSize(); ++j)
        {
            Transition tempTrans(automaton1.automaton.getSize(), automaton2.automaton[STARTING_VERTEX][j].getLetter());
            //addTransition(automaton1.finalStates[i], automaton1.automaton.getSize(), automaton2.automaton[STARTING_VERTEX][j].getLetter());
            tempArr.addElement(tempTrans);
        }
        this->automaton.addElement(tempArr);
    }
    
    // Copy all other transitions of automaton2 to result (this).
    for (unsigned int i = 1; i < automaton2.automaton.getSize(); ++i)
    {
        DynamicArray<Transition> tempArr;
        for (unsigned int j = 0; j < automaton2.automaton[i].getSize(); ++j)
        {
            if (automaton2.automaton[i][j].getToVertex() == STARTING_VERTEX)
            {
                for (unsigned k = 0; k < automaton1.finalStates.getSize(); ++k)
                {
                    // Copy transitions from vertices of automaton2 to the starting vertex of automaton2. The starting vertices in the new automaton are the final states of automaton1.
                    Transition tempTrans(automaton1.finalStates[k], automaton2.automaton[i][j].getLetter());
                    //this->addTransition(this->automaton.getSize(), automaton1.finalStates[k], automaton2.automaton[i][j].getLetter());
                    tempArr.addElement(tempTrans);
                }
            }
            else
            {
                
                // Calculate the new index in *this (result) of the vertex of the transition.
                unsigned newVertexIndex = automaton1.automaton.getSize() + automaton2.automaton[i][j].getToVertex() - 1;
               // this->addTransition(this->automaton.getSize(), newVertexIndex, automaton2.automaton[i][j].getLetter());
                Transition tempTrans(newVertexIndex, automaton2.automaton[i][j].getLetter());
                tempArr.addElement(tempTrans);
                
            }
        }
        this->automaton.addElement(tempArr);
    }
    
    
}

void Automaton::kleeneStar()
{
    Automaton result;
    // Copy transitions from the original starting vertex to the new starting vertex and increment the vertices indexes by one because of the addition of the new starting vertex.
    DynamicArray<Transition> tempArr;
    for (unsigned i = 0; i < this->automaton[STARTING_VERTEX].getSize(); ++i)
    {
        Transition tempTrans(this->automaton[STARTING_VERTEX][i].getToVertex() + 1, this->automaton[STARTING_VERTEX][i].getLetter());
        tempArr.addElement(tempTrans);
    }
    result.automaton.addElement(tempArr);
    
    // Copy transitions to the new automaton and increment vertex indexes by one because a new starting vertex will be added.
    for (unsigned i = STARTING_VERTEX; i < this->automaton.getSize(); ++i)
    {
        DynamicArray<Transition> tempArr1;
        for (unsigned j = 0; j < this->automaton[i].getSize(); ++j)
        {
            Transition tempTrans(this->automaton[i][j].getToVertex() + 1, this->automaton[i][j].getLetter());
            tempArr1.addElement(tempTrans);
        }
        result.automaton.addElement(tempArr1);
    }
    
    // Add transitions from all final states to all post-start vertices.
    for (unsigned i = 0; i < this->finalStates.getSize(); ++i)
    {
        for (unsigned j = 0; j < this->automaton[STARTING_VERTEX].getSize(); ++j)
        {
            if (!result.transitionExist(this->finalStates[i] + 1, this->automaton[STARTING_VERTEX][j].getToVertex() + 1, this->automaton[STARTING_VERTEX][j].getLetter()))
            {
                result.addTransition(this->finalStates[i] + 1, this->automaton[STARTING_VERTEX][j].getToVertex() + 1, this->automaton[STARTING_VERTEX][j].getLetter());
            }
        }
    }
    for (unsigned i = 0; i < this->finalStates.getSize(); ++i)
    {
        result.finalStates[i] = this->finalStates[i] + 1;
    }
    result.finalStates.addElement(STARTING_VERTEX);
    //  determine();
    *this = result;
}

void Automaton::determine()
{
    
}

//void Automaton::determine()
//{
//    std::queue<DynamicArray<ElementsOfNewVertices>> verticesSets;
//    Automaton* tempCopyOfThis = new Automaton(*this);
//    Automaton* result = new Automaton();
//
//
//        // Traversing all vertices, adjacent of STARTING_VERTEX.
//        for (unsigned j = 0; j < tempCopyOfThis->automaton[STARTING_VERTEX].getSize(); ++j)
//        {
//            // Add an array where all transitions with the same letter from vertexIndex will be stored temporarily.
//            DynamicArray<unsigned> elementsOfNewVertex;
//            char letter = tempCopyOfThis->automaton[STARTING_VERTEX][j].getLetter();
//            elementsOfNewVertex.addElement(tempCopyOfThis->automaton[STARTING_VERTEX][j].getToVertex());
//            // Remove the current vertex in order not to be copied again.
//            tempCopyOfThis->automaton[STARTING_VERTEX].removeElement(this->automaton[STARTING_VERTEX][j]);
//            for (unsigned k = j + 1; k < this->automaton[STARTING_VERTEX].getSize(); ++k)
//            {
//                if (letter == tempCopyOfThis->automaton[STARTING_VERTEX][k].getLetter())
//                {
//                    elementsOfNewVertex.addElement(tempCopyOfThis->automaton[j][k].getToVertex());
//                    tempCopyOfThis->automaton[j].removeElement(tempCopyOfThis->automaton[j][k]);
//                }
//            }
//            ElementsOfNewVertices temp;
//            if (checkIfFinalState(j))
//            {
//                temp.hasFinalState = true;
//            }
//            temp.elements = elementsOfNewVertex;
//            verticesSets.front().addElement(temp);
////            result->copyNewVerticesAndTransitions(verticesSets, result, STARTING_VERTEX, letter);
//
//        }
//    //while(!verticesSets.empty());
//
//    //free();
//    //delete tempCopyOfThis;
//    //this->automaton = result;
//}

void Automaton::totalize()
{
    unsigned errorState = automaton.getSize();
    // Add transitions with letters to the error state.
    DynamicArray<Transition> digitsAndLetters;
    for (char i = 'a'; i <= 'z'; ++i)
    {
        Transition temp(errorState, i);
        digitsAndLetters.addElement(temp);
    }
    // Add transitions with digits to the error state.
    for (char i = '0'; i <= '9'; ++i)
    {
        Transition temp(errorState, i);
        digitsAndLetters.addElement(temp);
    }
    // Add all transitions to the automaton.
    automaton.addElement(digitsAndLetters);
    // Add transitions with letters from all states to the error state.
    for (unsigned i = STARTING_VERTEX; i < automaton.getSize() - 1; ++i)
    {
        
        for (char h = 'a'; h <= 'z'; ++h)
        {
            bool transitionExist = false;
            for (unsigned j = 0; j < automaton[i].getSize(); ++j)
            {
                if (automaton[i][j].getLetter() == h)
                {
                    transitionExist = true;
                    break;
                }
            }
            if (!transitionExist)
            {
                this->addTransition(i, errorState, h);
            }
        }
    }
    // Add transitions with digits from all states to the error state.
    for (unsigned i = STARTING_VERTEX; i < automaton.getSize() - 1; ++i)
    {
        for (char h = '1'; h <= '9'; ++h)
        {
            bool transitionExist = false;
            for (unsigned j = 0; j < automaton[i].getSize(); ++j)
            {
                if (automaton[i][j].getLetter() == h)
                {
                    transitionExist = true;
                    break;
                }
            }
            if (!transitionExist)
            {
                this->addTransition(i, errorState, h);
            }
        }
    }
}

bool Automaton::acceptWord(const String& string, unsigned stringPos, unsigned vertex) const
{
    bool isAccapted = false;
    if (stringPos == string.getLen())
    {
        if (isFinal(vertex))
        {
            isAccapted = true;
            return isAccapted;
        }
        return isAccapted;
    }
    
    for (unsigned i = 0; i < automaton[vertex].getSize(); ++i)
    {
        if (automaton[vertex][i].getLetter() == string[stringPos])
        {
           return acceptWord(string, stringPos + 1, automaton[vertex][i].getToVertex());
        }
    }
    return isAccapted;
}

bool Automaton::acceptEmptyWord() const
{
    for (unsigned i = 0; i < finalStates.getSize(); ++i)
    {
        if (finalStates[i] == STARTING_VERTEX)
        {
            return true;
        }
    }
    return false;
}

void Automaton::addFinalState(unsigned state)
{
    finalStates.addElement(state);
}

std::ostream& operator<<(std::ostream& stream, const Automaton& rhs)
{
    for (unsigned i = 0; i < rhs.automaton.getSize(); ++i)
    {
        stream << i << " -> ";
        for (unsigned j = 0; j < rhs.automaton[i].getSize(); ++j)
        {
            stream << '(' << rhs.automaton[i][j].getLetter() << ',' << rhs.automaton[i][j].getToVertex() << ") ";
        }
        stream << '\n';
    }
    return stream;
}

void Automaton::addTransitionFromOutside(const DynamicArray<Transition> transitions)
{
    automaton.addElement(transitions);
}

bool Automaton::isFinal(unsigned state) const
{
    for (unsigned i = 0; i < finalStates.getSize(); ++i)
    {
        if (state == finalStates[i])
        {
            return true;
        }
    }
    return false;
}

bool Automaton::transitionExist(unsigned fromVertex, unsigned int toVertex, char letter) const
{
    for (unsigned i = 0; i < automaton[fromVertex].getSize(); ++i)
    {
        if (automaton[fromVertex][i].getLetter() == letter && automaton[fromVertex][i].getToVertex() == toVertex)
        {
            return true;
        }
    }
    return false;
}
