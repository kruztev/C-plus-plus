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
const unsigned short LENGTH_OF_LONGEST_PARAMETER = 5;

enum Commands {
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

enum Parameters {
    INVALID_PARAMETER = -1,
    
    BOTH,
    LEFT,
    RIGHT,
    
    PARAMETERS_COUNT
};

// Checking the input.
short action(std::string dictionary[], std::string buffer) {
    for (unsigned i = 0; i < COMMANDS_COUNT; ++i) {
        if (!strcasecmp(dictionary[i].c_str(), buffer.c_str())) {
            return i;
        }
    }
    return INVALID_COMMAND;
}

// Check wether the command requires arguments.
bool checkInput() {
    if ((char)std::cin.peek() == '\n') {
        std::cerr << "This command requiers arguments\n";
        std::cin.clear();
        std::cin.ignore(UINT32_MAX, '\n');
        return 0;
    }
    return 1;
}

// Function getNameQuotations extracts name between quotations marks. It is used in functions add and swap.
void getNameQuotations(std::string& name) {
    std::cin.ignore(2); // Ignores the white space between the command and the dancer name and the quotations mark.
    for (size_t i = 0; i <= MAX_NAME_SIZE; ++i) {
        char c = std::cin.get();
        if (c == '"')
            break;
        name.push_back(c);
    }
}

void getName(std::string& name) {
    char buffer[MAX_NAME_SIZE + 1];
    std::cin.ignore();
    std::cin.getline(buffer, MAX_NAME_SIZE);
    name = buffer;
}

void getNameBeforeParameter(std::string& name) {
    char buffer[MAX_NAME_SIZE + 1];
    std::cin.ignore();
    unsigned short pos = 0; // It is necessary to extract the characters one by one in order to avoid the bracket of the parameter. Variable pos controls the position the next character will be written.
    for (unsigned short i = 0; i < MAX_NAME_SIZE; ++i) {
        char c = std::cin.get();
        if (std::cin.peek() == '[')
            break;
        buffer[pos++] = c;
    }
    buffer[pos] = '\0';
    name = buffer;
}

void extractParameter(std::string& parameter) {
    std::cin.ignore(); // Ignoring the parameter bracket.
    for (size_t i = 0; i < LENGTH_OF_LONGEST_PARAMETER; ++i) {
        char c = std::cin.get();
        if (c == ']')
            break;
        parameter.push_back(c);
    }
}

void release(HashTable& chainDance) {
    std::string dancer;
    getNameBeforeParameter(dancer);
    std::string parameter;
    extractParameter(parameter);
    std::string dictionary[] = {"both", "left", "right"};
    // Using 0 to release both neighbours, 1 to release the left neighbour and 2 to release the right neighbour.
    switch (action(dictionary, parameter)) {
        case 0:
            chainDance.grabOrRelease(dancer, 0, RELEASE);
            break;
        case 1:
            chainDance.grabOrRelease(dancer, 1, RELEASE);
            break;
        case 2:
            chainDance.grabOrRelease(dancer, 2, RELEASE);
            break;
    }
    
}

void info(HashTable& chainDance) {
    std::string dancer;
    getName(dancer);
    chainDance.info(dancer);
}

void add(HashTable& chainDance, unsigned& countOfDancers) {
    std::string dancer;
    getNameQuotations(dancer);
    std::string leftNeighbour;
    getNameQuotations(leftNeighbour);
    std::string rightNeighbour;
    getNameQuotations(rightNeighbour);
    chainDance.add(dancer, leftNeighbour, rightNeighbour, countOfDancers);
}

void grab(HashTable& chainDance) {
    std::string dancer;
    getNameBeforeParameter(dancer);
    std::string parameter;
    extractParameter(parameter);
    std::string dictionary[] = {"both", "left", "right"};
    // Using 0 to release both neighbours, 1 to release the left neighbour and 2 to release the right neighbour.
    switch (action(dictionary, parameter)) {
        case 0:
            chainDance.grabOrRelease(dancer, 0, GRAB);
            break;
        case 1:
            chainDance.grabOrRelease(dancer, 1, GRAB);
            break;
        case 2:
            chainDance.grabOrRelease(dancer, 2, GRAB);
            break;
    }
}

void remove(HashTable& chainDance, unsigned& countOfDancers, std::string& leader, bool& enoughDancers) {
    std::string dancer;
    getName(dancer);
    chainDance.remove(dancer, countOfDancers, leader, enoughDancers);
}

void swap(HashTable& chainDance, std::string& leader) {
    std::string dancer1;
    getNameQuotations(dancer1);
    std::string dancer2;
    getNameQuotations(dancer2);
    chainDance.swap(dancer1, dancer2, leader);
    
}

void loadChainDanceFromFile(HashTable& chainDance, std::string& leader, unsigned& countOfDancers, std::ifstream& stream) {
//    std::ifstream stream("dancers.txt");
    
    char buffer[MAX_NAME_SIZE + 1];
    stream.getline(buffer, MAX_NAME_SIZE);
    if (stream.eof()) {
        std::cerr << "The file has no content\n";
        return;
    }
    leader = buffer;
    
    char bufferPrevious[MAX_NAME_SIZE+1];
    
    char bufferCurrent[MAX_NAME_SIZE+1];
    strcpy(bufferCurrent, leader.c_str());
    
    char bufferNext[MAX_NAME_SIZE+1];
    stream.getline(bufferNext, MAX_NAME_SIZE);
    
    chainDance.addFromFile(bufferCurrent, bufferNext, "\0", countOfDancers); // As the leader is added first, he has no right neighbour, so "\0" is written.
    strcpy(bufferPrevious, leader.c_str());
    strcpy(bufferCurrent, bufferNext);
    
    while(!stream.eof()) {
        stream.getline(bufferNext, MAX_NAME_SIZE);
        chainDance.addFromFile(bufferCurrent, bufferNext, bufferPrevious, countOfDancers);
        strcpy(bufferPrevious, bufferCurrent);
        strcpy(bufferCurrent, bufferNext);
    }
    chainDance.addFromFile(bufferCurrent, "\0", bufferPrevious, countOfDancers); // There is no participant after the last, so "\0" is written.
    // Edit the neighbours of the first and the last participant.
    chainDance.getDancer(bufferCurrent).leftNeighbour = leader;
    chainDance.getDancer(leader).rightNeighbour = bufferCurrent;
    
    stream.close();
}

void handleCommands(HashTable& chainDance, std::string& leader, unsigned& countOfDancers) {
    std::string dictionary[] = {"release", "grab", "info", "add", "remove", "swap", "print", "quit"};
    bool enoughDancers = true;
    while (enoughDancers) {
        std::string commandBuffer;
        std::cin >> commandBuffer;
        switch (action(dictionary, commandBuffer)) {
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
                remove(chainDance, countOfDancers, leader, enoughDancers);
                break;
            case 5:
                swap(chainDance, leader);
                break;
            case 6:
                chainDance.print(leader);
                break;
            case 7:
                return;
        }
    }
}

int main(int argc, const char* argv[]) {
    std::cout << "Commands <add> and <swap> require the names of the participants to be written in quotation marks.\n";
    std::cout << "For example: swap \"goliamata bira\" \"babata\"\n";
    
    std::ifstream stream((argv[1]));
    if (!stream) {
        std::cerr << "Cannot open file for reading\n";
        return 1;
    }
    
    HashTable chainDance;
    unsigned countOfDancers = 0;
    std::string leader;
    loadChainDanceFromFile(chainDance, leader, countOfDancers, stream);
    handleCommands(chainDance, leader, countOfDancers);
    
    return 0;
}
