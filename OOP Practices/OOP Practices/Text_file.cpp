//
//  Text_file.cpp
//  OOP Practices
//
// Problem solving test - work with text files.
//

#include <iostream>
#include <fstream>

const unsigned short COUNT_OF_PEOPLE = 3;
const unsigned short BUFFER_SIZE = 1024;
const unsigned short MAX_NAME_LENGTH = 128;

class Person
{
public:
    void setFirstName(const char[]);
    void setLastName(const char[]);
    void setFn(unsigned long long);
    void setGrade(unsigned short);
    
    const char* getFirstName() const;
    const char* getLastName() const;
    unsigned long long getFn() const;
    unsigned short getGrade() const;
    
private:
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    unsigned long long fn;
    unsigned short grade;
};

void Person::setFirstName(const char rhs[])
{
    strcpy(firstName, rhs);
}

void Person::setLastName(const char rhs[])
{
    strcpy(lastName, rhs);
}

void Person::setFn(unsigned long long fn)
{
    this->fn = fn;
}

void Person::setGrade(unsigned short grade)
{
    this->grade = grade;
}

const char* Person::getFirstName() const
{
    return firstName;
}

const char* Person::getLastName() const
{
    return lastName;
}

unsigned long long Person::getFn() const
{
    return fn;
}

unsigned short Person::getGrade() const
{
    return grade;
}

std::ostream& operator<<(std::ostream& stream, const Person& rhs)
{
    stream << rhs.getFn() << ' ' << rhs.getFirstName() << ' ' << rhs.getLastName() << ' ' << rhs.getGrade() << '\n';
    return stream;
}

std::istream& operator>>(std::istream& stream, Person& rhs)
{
    char buffer[MAX_NAME_LENGTH];
    char buffer2[MAX_NAME_LENGTH];
    unsigned long temp;
    stream >> temp;
    rhs.setFn(temp);
    stream >> buffer;
    rhs.setFirstName(buffer);
    stream >> buffer2;
    rhs.setLastName(buffer2);
    stream >> temp;
    rhs.setGrade(temp);
    return stream;
}

void deleteMemeber(unsigned long long number, const char filename[])
{
    std::ofstream temp("temp.txt");
    std::ifstream file(filename);
    if(!file || !temp)
    {
        std::cerr << "Cannot open files\n";
        return;
    }
    Person tempPerson;
    while(!file.eof())
    {
        file >> tempPerson;
        if(file.eof())
        {
            break;
        }
        if(tempPerson.getFn() == number)
        {
            continue;
        }
        temp << tempPerson;
    }
    
    temp.close();
    file.close();
    
    std::ofstream file2(filename, std::ios::trunc);
    std::ifstream temp2("temp.txt");
    if(!file2 || !temp2)
    {
        std::cerr << "Cannot open files\n";
        return;
    }
    char buffer[BUFFER_SIZE];
    while(!temp2.eof())
    {
        temp2.getline(buffer, BUFFER_SIZE);
        if(temp2.eof())
        {
            break;
        }
        file2 << buffer;
        file2 << '\n';
    }
    file2.close();
    temp2.close();
}


void create2()
{
    Person temp;
    std::ofstream file("StudentsGrades.txt", std::ios::app);
    if(!file)
    {
        std::cerr << "Cannot open file\n";
        return;
    }
    
    for(size_t i = 0; i < COUNT_OF_PEOPLE; ++i)
    {
        std::cin >> temp;
        file << temp;
        std::cout << "Record saved!\n";
    }
    
    file.close();
}

void sequentialSearch2()
{
    Person temp;
    unsigned long long fn;
    std::cin >> fn;
    std::fstream file("StudentsGrades.txt");
    if(!file)
    {
        std::cerr << "Cannot open file\n";
        return;
    }
    
    while(!file.eof())
    {
        file >> temp;
        if (temp.getFn() == fn)
        {
            std::cout << temp;
            break;
        }
        if (file.eof())
        {
            break;
        }
        std::cout << "Record not found!\n";
    }
    file.close();
}


