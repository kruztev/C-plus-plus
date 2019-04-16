//
//  Student_struct.cpp
//  OOP Practices
//

#include <iostream>
#include <fstream>

const unsigned short MAX_NAME_LENGTH = 50;

struct Student
{
public:
    Student ();
    Student (const Student&);
    Student& operator= (const Student&);
    ~Student();
    
public:
    void serialize(std::ofstream&);
    void deserialize(std::ifstream&);
    const char* getName() const;
    const unsigned int getFacultyNumber() const;
    
private:
    void enterName(); // Винаги изисква аргумент
    void enterFacultyNumber();
    void copyName(const char*);
    void clear();
    
private:
    char* name;
    unsigned int facultyNumber;
};

void Student::serialize(std::ofstream& fileOut)
{
    Student temp;
    fileOut.write((const char*) &temp, sizeof(Student));
}

void Student::deserialize(std::ifstream& fileIn)
{
    Student temp;
    fileIn.read((char*) &temp, sizeof(Student));
}

Student::Student ()
{
    enterName();
    enterFacultyNumber();
}

Student::Student(const Student& newStudent)
{
    *this = newStudent;
}

Student& Student::operator=(const Student& newStudent)
{
    if(this != &newStudent)
    {
        copyName(newStudent.name);
        facultyNumber = newStudent.facultyNumber;
    }
    return *this;
}

Student::~Student()
{
    clear();
}

void Student::clear()
{
    delete[] name;
}

void Student::copyName(const char* newName)
{
    if (name)
    {
        clear();
    }
    name = new (std::nothrow) char[strlen(newName) + 1];
    if (!name)
    {
        std::cerr << "Cannot allocate memory\n";
        return;
    }
    strcpy(name, newName);
}



void Student::enterName()
{
    char* buffer = new (std::nothrow) char[MAX_NAME_LENGTH];
    if(!buffer)
    {
        std::cerr << "Cannot allocate memory for name\n";
        return;
    }
    std::cin.getline(buffer, MAX_NAME_LENGTH, '\n');
    name = new (std::nothrow) char[strlen(buffer) + 1];
    if (!name)
    {
        std::cerr << "Cannot allocate memory for name\n";
        return;
    }
    strcpy(name, buffer);
    delete[] buffer;
}

void Student::enterFacultyNumber()
{
    std::cin >> facultyNumber;
}

const char* Student::getName() const
{
    char* copy = new (std::nothrow) char[strlen(name) + 1];
    if (!copy)
    {
        std::cerr << "Cannot allocate memory for name\n";
        return nullptr;
    }
    strcpy(copy, name);
    return copy;
}

const unsigned int Student::getFacultyNumber() const
{
    return facultyNumber;
}
