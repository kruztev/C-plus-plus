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
    void insertDancer(const std::string& name);
    const Dancer& getDancer(const std::string& name) const;
    Dancer& getDancer(const std::string& name);
    void removeFromList(const std::string& name);
    void print(const std::string&) const;
    void addFromFile(const std::string&name, const std::string& leftPerson, const std::string& rightPerson, unsigned& countOfDancers);
    
private:
    unsigned long hashFunction (const std::string& key, unsigned long size) const;
    void rehash();
    
public:
    void grabOrRelease(const std::string& name, unsigned parameter, bool flag);
    void info(const std::string& name) const;
    void add(const std::string& newDancerName, const std::string& leftDancer, const std::string& rightDancer, unsigned& countOfDancers);
       void remove(const std::string& name, unsigned& countOfDancers, std::string& leader, bool& enoughDancers);
    void swap(const std::string& dancer1Name, const std::string& dancer2Name);
};
