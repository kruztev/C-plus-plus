//
//  Student.cpp
//  OOP Practices
//

#include "Student.hpp"


Student::Student()
{
    facultyNumber = 0;
    countOfMarks = 0;
    marks = nullptr;
}

Student::Student(size_t newFacultyNumber, size_t newCountOfMarks)
{
    setFacultyNumber(newFacultyNumber);
    setCountOfMarks(newCountOfMarks);
    setMarks();
}

Student& Student::operator=(const Student& newStudent)
{
    if (this != &newStudent)
    {
        facultyNumber = newStudent.getFacultyNumber();
        countOfMarks = newStudent.getCountOfMArks();
        copyMarks(newStudent);
    }
    return *this;
}

Student::Student(const Student& newStudent)
{
    *this = newStudent;
}

Student::~Student()
{
    delete[] marks;
    marks = nullptr;
}

void Student::setFacultyNumber(size_t newFacultyNumber)
{
    facultyNumber = newFacultyNumber;
}

void Student::setCountOfMarks(size_t newCountOfMarks)
{
    countOfMarks = newCountOfMarks;
}

void Student::setMarks()
{
    if(!marks)
    {
        std::cerr << "The value for marks is invalud\n";
        return;
    }
    marks = new (std::nothrow) size_t[countOfMarks];
    if(!marks)
    {
        std:: cerr << "Cannot allocare memory\n";
        return;
    }
    
    for(size_t i = 0; i < countOfMarks; ++i)
    {
        std::cin >> marks[i];
    }
    return;
}

const size_t Student::getFacultyNumber() const
{
    return facultyNumber;
}

const size_t Student::getCountOfMArks() const
{
    return countOfMarks;
}

void Student::getMarks() const
{
    if (!marks)
    {
        std::cerr << "There are no marks entered yet\n";
        return;
    }
    for (size_t i = 0; i < countOfMarks; ++i)
    {
        std::cout << marks[i];
    }
}

void Student::copyMarks(const Student& newStudent)
{
    marks = new (std::nothrow) size_t[newStudent.countOfMarks];
    if(!marks)
    {
        std::cerr << "Cannot allocate memory\n";
        return;
    }
    for(size_t i = 0; i < newStudent.countOfMarks; ++i)
    {
        marks[i] = newStudent.marks[i];
    }
}
