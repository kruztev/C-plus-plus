//  Code ran and tested on Clang (Xcode Version 10.1)
//
//  main.cpp
//  Conga
//

#include <iostream>
#include "Vector.hpp"

const unsigned short BUFFER_SIZE = 256;
const unsigned short NAME_LEN = 32;
const unsigned short UNI_LEN = 8;

const char* universityDict[] = {"FMI", "TU", "UNSS"};

enum Commands
{
  INVALID_COMMAND = -1,
    
    APPEND,
    REMOVE_LAST,
    REMOVE_FIRST,
    REMOVE,
    MERGE,
    PRINT,
    QUIT,
    
    COMMANDS_COUNT
};

short action(const char* dictionary[], const char* buffer) // Checking the input.
{
    for(unsigned i = 0; i < COMMANDS_COUNT; ++i)
    {
        if(!strcasecmp(dictionary[i], buffer))
        {
            return i;
        }
    }
    return INVALID_COMMAND;
}

bool checkInput() // Check wether the command requires arguments.
{
    if((char)std::cin.peek() == '\n')
    {
        std::cerr << "This command requiers arguments. Try again.\n";
        std::cin.clear();
        std::cin.ignore(UINT32_MAX, '\n');
        return 0;
    }
    return 1;
}

short universityIsValid(const char* universityDict[], const char* newUniversity)
{
    for(unsigned i = 0; i < UNIVERSITIES_COUNT; ++i)
    {
        if(!strcasecmp(universityDict[i], newUniversity))
        {
            return i;
        }
    }
    return INVALID_UNIVERSITY;
}

void append(Vector& vector)
{
    char name[NAME_LEN] = {0,};
    std::cin >> name;
    char uni[UNI_LEN] = {0,};
    std::cin >> uni;
    short university = universityIsValid(universityDict, uni);
    if(university == INVALID_UNIVERSITY)
    {
        std::cerr << "Invalid university" << std::endl;
        return;
    }
    unsigned lineIndex;
    std::cin >> lineIndex;
    vector.append(name, (University)university, lineIndex);
}

void removeLast(Vector& vector)
{
    unsigned lineIndex;
    std::cin >> lineIndex;
    vector.removeLast(lineIndex);
}

void removeFirst(Vector& vector)
{
    unsigned lineIndex;
    std::cin >> lineIndex;
    vector.removeFirst(lineIndex);
}

void remove(Vector& vector)
{
    char name[NAME_LEN] = {0,};
    std::cin >> name;
    unsigned lineIndex;
    std::cin >> lineIndex;
    vector.removeByNameVector(name, lineIndex);
}

void merge(Vector& vector)
{
    unsigned lineIndex1, lineIndex2;
    std::cin >> lineIndex1;
    //std::cin.ignore(); // Ignores the white space between the two arguments lineIndex1 and lineIndex2.
    std::cin >> lineIndex2;
    vector.merge(lineIndex1, lineIndex2);
}

int main()
{
    const char* dictionary[] = {"append", "removeLast", "removeFirst", "remove", "merge", "print", "quit"}; // Dictionary with commands.
    bool programRuns = true; // This flag controls when the program ends.
    bool cycleHasStarted = false; // This flag indicates wether the while cycle has started so the conga of Integralcho have to be added. If it is true, the conga has been already added.
    
    Vector vector;
    
    while(programRuns)
    {
        if(!cycleHasStarted)
        {
            const char integralcho[] = "Integralcho";
            LinkedList* firstConga = new LinkedList(integralcho, FMI);
            vector.addConga(firstConga);
            cycleHasStarted = true;
        }

        char buffer[BUFFER_SIZE];
        std::cin >> buffer;
        
        switch (action(dictionary, buffer)) {
            case APPEND:
                if(!checkInput())
                {
                    break;
                }
                append(vector);
                break;
                
            case REMOVE_LAST:
                if(!checkInput())
                {
                    break;
                }
                removeLast(vector);
                break;
                
            case REMOVE_FIRST:
                if(!checkInput())
                {
                    break;
                }
                removeFirst(vector);
                break;
                
            case REMOVE:
                if(!checkInput())
                {
                    break;
                }
                remove(vector);
                break;
                
            case MERGE:
                if(!checkInput())
                {
                    break;
                }
                merge(vector);
                break;
                
            case PRINT:
                vector.printVector();
                break;
                
            case QUIT:
                programRuns = false;
                break;
                
            case INVALID_COMMAND:
                std::cerr << "Invalid command\n";
                break;
        }
    }
    
    return 0;
}
