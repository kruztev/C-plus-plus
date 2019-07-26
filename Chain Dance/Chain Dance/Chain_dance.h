//
//  Alexander Krustev 45314
//
//  Chain_dance.h
//  Chain Dance
//

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>

// Ivan Filipov's hash table example used
class HashTable {

private:
    struct Data {
        std::string name;
        std::string leftNeighbour;
        std::string rightNeighbour;
        bool grabbedLeft = false;
        bool grabbedRight = false;
        
        Data(std::string nName = "", std::string nameOfLeftNeighbour = "", std::string nameOfRightNeighbour = "") :
            name(nName),
            leftNeighbour(nameOfLeftNeighbour),
            rightNeighbour(nameOfRightNeighbour),
            grabbedLeft(true),
            grabbedRight(true)
        {}
        
        bool operator==(const Data&) const;
    };
private:
    typedef std::vector<std::list<Data>> table;
    table chainDance;
    typedef std::list<Data>::iterator iterator;
    
public:
    HashTable();
    
    
public:
    void insertElement(const std::string&);
    Data& getElement(const std::string&);
    void removeElement(const std::string&);
    void print(std::string);
    void addFromFile(const std::string&, const std::string&, const std::string&, unsigned);
    
private:
    unsigned hashFunction (const std::string&, unsigned);
    void rehash();
    
public:
    void release(const std::string, unsigned);
    void grab(const std::string, unsigned);
    void info(const std::string);
    void add(const std::string&, const std::string&, const std::string&, unsigned);
    void remove(const std::string&, unsigned, std::string&);
    void swap(const std::string&, const std::string&);
};
