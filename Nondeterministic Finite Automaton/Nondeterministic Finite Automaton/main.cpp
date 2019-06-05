//
//  main.cpp
//  Nondeterministic Finite Automaton
//

#include <iostream>
#include "Automaton.h"

void constructAutomaton1(Automaton& a)
{
    Transition t1(1, 'b');
    Transition t2(1, 'b');
    Transition t3(2, 'a');
    Transition t4(2, 'a');
    
    DynamicArray<Transition> arr1;
    arr1.addElement(t1);
    DynamicArray<Transition> arr2;
    arr2.addElement(t2);
    arr2.addElement(t3);
    DynamicArray<Transition> arr3;
    arr3.addElement(t4);
    
    a.addTransitionFromOutside(arr1);
    a.addTransitionFromOutside(arr2);
    a.addTransitionFromOutside(arr3);
    
    a.addFinalState(2);
}

void constructAutomaton2(Automaton& b)
{
    Transition t1(1, 'a');
    Transition t3(2, 'b');
    
    DynamicArray<Transition> arr1;
    arr1.addElement(t1);
    DynamicArray<Transition> arr3;
    arr3.addElement(t3);
    
    b.addTransitionFromOutside(arr1);
    b.addTransitionFromOutside(arr3);
    
    b.addFinalState(2);
}

void constructAutomaton3(Automaton& a)
{
    Transition t1(1, 'a');
    Transition t2(3, 'b');
    Transition t3(2, 'b');
    Transition t4(3, 'a');
    Transition t5(4, 'b');
    Transition t6(0, 'a');
    Transition t7(4, 'a');
    Transition t8(4, 'b');
    Transition t9(4, 'a');
    Transition t10(4, 'b');
    
    DynamicArray<Transition> vertex0;
    vertex0.addElement(t1);
    vertex0.addElement(t2);
    DynamicArray<Transition> vertex1;
    vertex1.addElement(t3);
    vertex1.addElement(t4);
    DynamicArray<Transition> vertex2;
    vertex2.addElement(t5);
    vertex2.addElement(t6);
    DynamicArray<Transition> vertex3;
    vertex3.addElement(t7);
    vertex3.addElement(t8);
    DynamicArray<Transition> vertex4;
    vertex4.addElement(t9);
    vertex4.addElement(t10);
    
    a.addTransitionFromOutside(vertex0);
    a.addTransitionFromOutside(vertex1);
    a.addTransitionFromOutside(vertex2);
    a.addTransitionFromOutside(vertex3);
    a.addTransitionFromOutside(vertex4);
    
//    a.addFinalState(0);
    a.addFinalState(3);
    a.addFinalState(2);

}

int main()
{
//    Automaton a, b, c;
//    constructAutomaton1(a);
//    constructAutomaton2(b);
//    std::cout << a << '\n';
//    std::cout << b << '\n';
//  c = a.unionOf2(b);
//  c = a.concatenationOf2(b);
//  std::cout << c << '\n';
    
    Automaton d, e;
    constructAutomaton3(d);
    constructAutomaton3(e);
    std::cout << "The automaton looks like this:\n";
    std::cout << d << '\n';
    std::cout << "Does the automaton accept \"ab\"?\n";
    std::cout << d.acceptWord("ab") << '\n';
    std::cout << "Does the automaton accept \"abb\"?\n";
    std::cout << d.acceptWord("abb") << '\n';
    std::cout << "Does the automaton accept the empty language?\n";
    std::cout << d.acceptEmptyWord() << '\n';
    std::cout << "The Kleene star of the automaton changes it like:\n";
    d.kleeneStar();
    std::cout << d << '\n';
    std::cout << "The automaton totalized looks like this:\n";
    e.totalize();
    std::cout << e << '\n';

    return 0;
}
