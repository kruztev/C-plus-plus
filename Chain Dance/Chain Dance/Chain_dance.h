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
    struct Dancer {
        Dancer(std::string nName = "", std::string nameOfLeftNeighbour = "", std::string nameOfRightNeighbour = "") :
            name(nName),
            leftNeighbour(nameOfLeftNeighbour),
            rightNeighbour(nameOfRightNeighbour),
            grabbedLeft(true),
            grabbedRight(true)
        {}
        bool operator==(const Dancer&) const;
        
        std::string name;
        std::string leftNeighbour;
        std::string rightNeighbour;
        bool grabbedLeft = false;
        bool grabbedRight = false;
    };
private:
    typedef std::vector<std::list<Dancer>> table;
    table chainDance;
    typedef std::list<Dancer>::iterator iterator;
    
public:
    HashTable();
    
    
public:
    void insertDancer(const std::string&);
    Dancer& getDancer(const std::string&);
    void removeDancer(const std::string&);
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
