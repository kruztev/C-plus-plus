//
//  main.cpp
//  OOP Practices
//

#include <iostream>
#include <fstream>
#include "Date.h"

// Problem solving test - work with binary files.

const unsigned short MAX_NAME_LENGTH = 256;

struct Student
{
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    unsigned long long fn;
    unsigned short grade;
};

void create()
{
    Student temp;
    std::cin >> temp.fn;
    std::cin >> temp.firstName;
    std::cin >> temp.lastName;
    std::cin >> temp.grade;

    std::ofstream file("StudentsGrades.db", std::ios::binary | std::ios::app);
    if(!file)
    {
        std::cerr << "Cannot open file\n";
        return;
    }
    file.write((const char*)&temp, sizeof(Student));
    std::cout << "Record saved!\n";
    file.close();
}

void sequentialSearch()
{
    Student temp;
    unsigned long long fn;
    std::cin >> fn;
    std::fstream file("StudentsGrades.db", std::ios::binary);
    if(!file)
    {
        std::cerr << "Cannot open file\n";
        return;
    }

    while(!file.eof())
    {
        file.read((char*)&temp, sizeof(Student));
        if (temp.fn == fn)
        {
            std::cout << temp.fn << ' ' << temp.firstName << ' ' << temp.lastName << ' ' << temp.grade;
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

int main()
{
    const char* dictionary[] = {"create", "sequentialSearch", "exit"};
    char buffer[1024];
    while(true)
    {
        std::cin >> buffer;
        if (!strcmp(buffer, dictionary[0]))
        {
            create();
            continue;
        }
        if(!strcmp(buffer, dictionary[1]))
        {
            sequentialSearch();
            continue;
        }
        if(!strcmp(buffer, dictionary[2]))
        {
            break;
        }
    }
    return 0;
}
