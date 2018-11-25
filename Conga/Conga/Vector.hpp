//  Code ran and tested on Clang (Xcode Version 10.1)
//
//  Vector.hpp
//  Conga
//

#ifndef Vector_hpp
#define Vector_hpp

#include "LinkedList.hpp"

class Vector
{
public:
    Vector();
//    Copy constructor and operator= are presented just to show the data structure Vector. In the program only one vector is needed, so theese two are added as comments.
//    Vector(const Vector&);
//    Vector& operator=(const Vector&);
    ~Vector();
    
public:
    void updateArray(unsigned);
    void addConga(LinkedList*);
    void removeByNameVector(const char*, unsigned);
    void merge(unsigned, unsigned);
    void printVector() const;
    void append(const char*, University, unsigned);
    void removeLast(unsigned);
    void removeFirst(unsigned);
    
private:
    void resize();
    void clear();
    void copy(const Vector&);
    
private:
    LinkedList** arr;
    unsigned size;
    unsigned capacity;
};



#endif
