//
//  StudentsTable.cpp
//  SDP Practs
//

#include "StudentsTable.hpp"

const unsigned short MAX_GRADE = 6;

void StudentsTable::CountingSort()
{
    
    
    unsigned short grades[MAX_GRADE] = {0,};
    unsigned size = arr.getSize();
    for(unsigned i = 0; i < size; ++i)
    {
        unsigned short temp = arr[i].grade;
        grades[temp]++;
    }
    
    // Префиксен масив
    for(unsigned i = 1; i < MAX_GRADE; ++i)
    {
        grades[i] += grades[i-1];
    }
    
    Vector<Student> copy;
    
    for(unsigned i = 0; i < size; ++i)
    {
        unsigned pos = --grades[arr[i].grade];
        copy[pos] = arr[i];
    }
}

