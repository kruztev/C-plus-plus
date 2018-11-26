//
//  StudentsTable.hpp
//  SDP Practs
//


#ifndef StudentsTable_hpp
#define StudentsTable_hpp

#include "Student.hpp"
#include "Vector.hpp"

class StudentsTable
{
public:
    StudentsTable();
    StudentsTable(const StudentsTable&);
    StudentsTable& operator=(const StudentsTable&);
    ~StudentsTable();
    
public:
    void CountingSort();
    
private:
    Vector<Student> arr;
    
};



#endif 
