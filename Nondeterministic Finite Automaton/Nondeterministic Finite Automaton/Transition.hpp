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
    Transition(const Transition&) = default;
    Transition& operator=(const Transition&) = default;
    ~Transition() = default;
    
private:
    unsigned vertex;
    char letter;
};

#endif
