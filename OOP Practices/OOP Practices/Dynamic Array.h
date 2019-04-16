//
//  Dynamic Array.h
//  OOP Practices
//

#ifndef Dynamic_Array_hpp
#define Dynamic_Array_hpp

#include <iostream>
#include "Clock.h"

class DynamicArray
{
public:
    DynamicArray();
    DynamicArray(const DynamicArray&);
    DynamicArray& operator=(const DynamicArray&);
    ~DynamicArray();
    
public:
    void addClock(const Clock&);
    void removeClock();
    
private: // Help functions
    void copy(const DynamicArray&);
    void clear();
    void resize();
    
    
private:
    Clock* arr;
    size_t size;
    size_t capacity;
};


#endif
