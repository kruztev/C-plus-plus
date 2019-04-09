//
//  Files.cpp
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

//int main()
//{
//    std::cout << "Test\n";
//    size_t n = 0;
//    std::cin >> n;
//    std::cin.ignore();
//    
//    std::ofstream fileOut ("students", std::ios::binary);
//    if(!fileOut)
//    {
//        std::cerr << "Cannot open file\n";
//        return -1;
//    }
//    
//    fileOut.write((const char*) &n, sizeof(size_t));
//    
//    for (size_t i = 0; i < n; ++i)
//    {
//        Student temp;
//        temp.serialize(fileOut);
//    }
//    
//    fileOut.close();
//    
//    std::ifstream fileIn ("students", std::ios::binary);
//    
//    if(!fileIn)
//    {
//        std::cerr << "Cannot open file\n";
//    }
//    
//    fileIn.read((char*) &n, sizeof(size_t));
//    
//    for(size_t i = 0; i < n; ++i)
//    {
//        Student temp;
//        temp.deserialize(fileIn);
//        std::cout << temp.getName();
//        std::cout << ' ';
//        std::cout << temp.getFacultyNumber();
//        std::cout << '\n';
//    }
//    
//    
//    return 0;
////    unsigned n;
////    std::cin >> n;
////
////    std::ofstream fileOut;
////    fileOut.open("test", std::ios::binary | std::ios::out);
////    if(!fileOut)
////    {
////        std::cerr << "Cannot open file\n";
////        return -1;
////    }
////
////    int temp;
////    for(size_t i = 0; i < n; ++i)
////    {
////        std::cin >> temp;
////        fileOut.write((const char*)&temp, sizeof(int));
////    }
////    fileOut.close();
////
////    std::ifstream fileIn;
////    fileIn.open("test", std::ios::binary | std::ios::in);
////    if(!fileIn)
////    {
////        std::cerr << "Cannot open file\n";
////        return -1;
////    }
////
////    for(size_t i = 0; i < n; ++i)
////    {
////        fileIn.read((char*)&temp, sizeof(int));
////        if (!fileIn.good())
////        {
////            break;
////        }
////        if (!(i % 3))
////        {
////            std::cout << temp << ' ';
////        }
////    }
//}

