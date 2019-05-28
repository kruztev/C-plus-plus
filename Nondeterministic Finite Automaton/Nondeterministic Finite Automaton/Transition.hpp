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
    
public:
    unsigned toVertex;
    char letter;
};

Transition::Transition(unsigned toVertex, char letter)
{
    this->toVertex = toVertex;
    this->letter = letter;
}

#endif
