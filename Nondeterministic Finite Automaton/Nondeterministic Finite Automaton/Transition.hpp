//
//  Transition.hpp
//  Nondeterministic Finite Automaton
//

#ifndef Transition_hpp
#define Transition_hpp

class Transition
{
public:
    Transition() = default;
    Transition(unsigned, char);
    Transition(const Transition&) = default;
    Transition& operator=(const Transition&) = default;
    ~Transition() = default;
    unsigned getToVertex() const;
    char getLetter() const;
    
private:
    unsigned toVertex;
    char letter;
};

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

#endif
