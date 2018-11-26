//
//  Stack.hpp
//  SDP Practs
//

#ifndef Stack_hpp
#define Stack_hpp

template <typename T>
class Stack
{
public:
    Stack();
    Stack(const Stack&);
    Stack& operator=(const Stack&);
    ~Stack();
  
public:
    void push(const T);
    T pop();
    T peak();
    bool isEmpty();
    
private:
    void copy(const Stack&);
    void clear();
    void resize();
    
private:
    T* arr;
    unsigned size;
    unsigned capacity;
};


bool isCorrect(char*, unsigned);

#endif
