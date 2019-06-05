//
//  Transition.h
//  Nondeterministic Finite Automaton
//

#ifndef Transition_h
#define Transition_h

class Transition
{
public:
    Transition() = default;
    Transition(unsigned, char);
    unsigned getToVertex() const;
    char getLetter() const;
    
private:
    unsigned toVertex;
    char letter;
};

#endif
