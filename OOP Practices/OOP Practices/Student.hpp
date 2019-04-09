//
//  Student.hpp
//  OOP Practices
//

#ifndef Student_h
#define Student_h

#include <iostream>

struct Student
{
public:
    Student(size_t, size_t);
    Student();
    Student(const Student&);
    Student& operator=(const Student&);
    ~Student();
    
public:
    void setFacultyNumber(size_t);
    void setCountOfMarks(size_t);
    void setMarks();
    
    const size_t getFacultyNumber() const;
    const size_t getCountOfMArks() const;
    void getMarks() const;
    
private:
    void copyMarks(const Student&);
    
private:
    size_t facultyNumber;
    size_t countOfMarks;
    size_t* marks;
    
};


#endif
