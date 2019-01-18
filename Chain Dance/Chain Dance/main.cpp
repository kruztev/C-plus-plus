//
//  Alexander Krustev 45314
//
//  main.cpp
//  Chain Dance
//


#include <iostream>
#include <fstream>
#include "Chain_dance.h"

const unsigned short MAX_NAME_SIZE = 30;

enum Commands
{
    INVALID_COMMAND = -1,
    
    RELEASE,
    GRAB,
    INFO,
    ADD,
    REMOVE,
    SWAP,
    PRINT,
    QUIT,
    
    COMMANDS_COUNT
};

enum Parameters
{
    INVALID_PARAMETER = -1,
    
    BOTH,
    LEFT,
    RIGHT,
    
    PARAMETERS_COUNT
};

short action(std::string dictionary[], std::string buffer) // Checking the input.
{
    for(unsigned i = 0; i < COMMANDS_COUNT; ++i)
    {
        if(!strcasecmp(dictionary[i].c_str(), buffer.c_str()))
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

void getName(std::string& name)
{
    char buffer[MAX_NAME_SIZE + 1];
    if(std::cin.get() == '"')
    {
        std::cin.getline(buffer, MAX_NAME_SIZE, '"');
    }
    name = buffer;
}

void release(HashTable chainDance)
{
    std::string dancer;
    getName(dancer);
    std::string parameter;
    std::cin >> parameter;
    std::string dictionary[] = {"both", "left", "right"};
    // Using 0 to release both neighbours, 1 to release the left neighbour and 2 to release the right neighbour.
    switch (action(dictionary, parameter))
    {
        case 0:
            chainDance.release(dancer, 0);
            break;
        case 1:
            chainDance.release(dancer, 1);
            break;
        case 2:
            chainDance.release(dancer, 2);
            break;
    }
    
}

void info(HashTable chainDance)
{
    std::string dancer;
    getName(dancer);
    chainDance.info(dancer);
}

void add(HashTable chainDance, unsigned countOfDancers)
{
    std::string dancer;
    getName(dancer);
    std::string leftNeighbour;
    getName(leftNeighbour);
    std::string rightNeighbour;
    getName(rightNeighbour);
    chainDance.add(dancer, leftNeighbour, rightNeighbour, countOfDancers);
}

void grab(HashTable chainDance)
{
    std::string dancer;
    std::cin >> dancer;
    std::string parameter;
    std::cin >> parameter;
    std::string dictionary[] = {"both", "left", "right"};
    // Using 0 to release both neighbours, 1 to release the left neighbour and 2 to release the right neighbour.
    switch (action(dictionary, parameter))
    {
        case 0:
            chainDance.grab(dancer, 0);
            break;
        case 1:
            chainDance.grab(dancer, 1);
            break;
        case 2:
            chainDance.grab(dancer, 2);
            break;
    }
}

void remove(HashTable chainDance, unsigned countOfDancers, std::string& leader)
{
    std::string dancer;
    getName(dancer);
    chainDance.remove(dancer, countOfDancers, leader);
}

void swap(HashTable chainDance)
{
    std::string dancer1;
    getName(dancer1);
    std::string dancer2;
    getName(dancer2);
    chainDance.swap(dancer1, dancer2);
    
}


int main(int argc, const char* argv[]) {
    std::string dictionary[] = {"release", "grab", "info", "add", "remove", "swap", "print", "quit"};
    bool programRuns = true;
    
    HashTable chainDance;
    unsigned countOfDancers = 0;
    std::string leader;
    std::ifstream stream;
    //stream.open(argv[1], std::ios::in);
    stream.open("test.txt", std::ios::in);
    if(!stream)
    {
        std::cerr << "Cannot open file for reading.\n";
        return -1;
    }
    if(!stream.eof())
    {
        char buffer[MAX_NAME_SIZE+1];
        stream.getline(buffer, MAX_NAME_SIZE);
        leader = buffer;
    }
    
    char bufferPrevious[MAX_NAME_SIZE+1];
    strcpy(bufferPrevious, leader.c_str());

    char bufferCurrent[MAX_NAME_SIZE+1];
    strcpy(bufferCurrent, leader.c_str());

    char bufferNext[MAX_NAME_SIZE+1];
    stream.getline(bufferNext, MAX_NAME_SIZE);

    chainDance.addFromFile(bufferCurrent, bufferPrevious, bufferNext, countOfDancers);
    strcpy(bufferCurrent, bufferNext);
    
    while(!stream.eof())
    {
        //stream.getline(bufferCurrent, MAX_NAME_SIZE);
        stream.getline(bufferNext, MAX_NAME_SIZE);
        if(stream.eof())
            break;
        chainDance.addFromFile(bufferCurrent, bufferPrevious, bufferNext, countOfDancers);
        strcpy(bufferPrevious, bufferCurrent);
        strcpy(bufferCurrent, bufferNext);
    }
    chainDance.addFromFile(bufferNext, bufferCurrent, leader, countOfDancers);
    chainDance.getElement(leader).leftNeighbour = bufferNext;
    
    stream.close();
    
    while (programRuns)
    {
        std::string commandBuffer;
        std::cin >> commandBuffer;
        switch (action(dictionary, commandBuffer))
        {
            case 0:
                if(!checkInput())
                    break;
                release(chainDance);
                break;
            case 1:
                grab(chainDance);
                break;
            case 2:
                info(chainDance);
                break;
            case 3:
                add(chainDance, countOfDancers);
                break;
            case 4:
                remove(chainDance, countOfDancers, leader);
                break;
            case 5:
                swap(chainDance);
                break;
            case 6:
                chainDance.print(leader);
                break;
            case 7:
                programRuns = false;
                break;
        }
    }
    
    return 0;
}
