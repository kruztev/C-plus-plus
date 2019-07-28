//
//  Alexander Krustev 45314
//
//  Hash_table.cpp
//  Chain Dance
//


#include "Chain_dance.h"

const unsigned short MAX_CHAIN_SIZE = 3;
const unsigned short STARTING_SIZE = 8;

HashTable::HashTable() :
chainDance(STARTING_SIZE)
{}

unsigned long HashTable::hashFunction(const std::string& key, unsigned long size) const {
    unsigned long result = key.size();
    unsigned long limit = result;
    for (unsigned i = 0; i < limit; ++i) {
        result += (unsigned)key[i];
    }
    return result % size;
}

void HashTable::insertDancer(const std::string& name) {
    unsigned long index = hashFunction(name, chainDance.size());
    for (iterator t = chainDance[index].begin(); t != chainDance[index].end(); ++t) {
        if (t.operator*().name == name) {
            std::cout << "This person has already been added to the chain dance.\n";
            return;
        }
    }
    if (chainDance[index].size() >= MAX_CHAIN_SIZE) {
        rehash();
        index = hashFunction(name, chainDance.size());
    }
    Dancer newDancer = Dancer(name);
    chainDance[index].push_front(newDancer);
}

void HashTable::rehash() {
    table temp(chainDance.capacity()*2);
    for (unsigned index = 0; index < chainDance.size(); ++index) {
        if (!chainDance[index].empty()) {
            for (iterator t = chainDance[index].begin(); t != chainDance[index].end(); ++t) {
                unsigned long newIndex = hashFunction((*t).name, temp.size());
                temp[newIndex].push_front(*t);
            }
        }
    }
    chainDance = temp;
}

HashTable::Dancer& HashTable::getDancer(const std::string& name) {
    unsigned long index = hashFunction(name, chainDance.size());
    if (chainDance[index].empty()) {
        throw std::logic_error("No person named like that.\n");
    }
    else if (name == chainDance[index].front().name) {
        return chainDance[index].front();
    }
    else {
        for (iterator t = ++chainDance[index].begin(); t != chainDance[index].end(); ++t) {
            if (name == (*t).name) {
                return *t;
            }
        }
    }
    throw std::logic_error("No person named like that.\n");
}

const HashTable::Dancer& HashTable::getDancer(const std::string& name) const {
    unsigned long index = hashFunction(name, chainDance.size());
    if (chainDance[index].empty()) {
        throw std::logic_error("No person named like that.\n");
    }
    else if (name == chainDance[index].front().name) {
        return chainDance[index].front();
    }
    else {
        for (std::list<Dancer>::const_iterator t = ++chainDance[index].begin(); t != chainDance[index].end(); ++t) {
            if (name == (*t).name) {
                return *t;
            }
        }
    }
    throw std::logic_error("No person named like that.\n");
}

void HashTable::removeDancer(const std::string& name) {
    // Check if element exist?
     unsigned long index = hashFunction(name, chainDance.size());
    chainDance[index].remove(getDancer(name));
}

void HashTable::print(const std::string& leader) const {
    std::cout << leader << '\n';
    std::string temp = getDancer(leader).leftNeighbour;
    while (temp != leader) {
        std::cout << temp << '\n';
        temp = getDancer(temp).leftNeighbour;
    }
}

bool HashTable::Dancer::operator==(const Dancer& nDancer) const {
   return (this->name == nDancer.name) ? true : false;
}

void HashTable::release(const std::string& name, unsigned parameter) {
// Using 0 to release both neighbours, 1 to release the left neighbour and 2 to release the right neighbour.
    switch (parameter) {
        case 0:
            getDancer(name).grabbedLeft = 0;
            getDancer(name).grabbedRight = 0;
            break;
        case 1:
            getDancer(name).grabbedLeft = 0;
            break;
        case 2:
            getDancer(name).grabbedRight = 0;
            break;
    }
}

void HashTable::grab(const std::string& name, unsigned parameter) {
    // Using 0 to grab both neighbours, 1 to grab the left neighbour and 2 to grab the right neighbour.
    switch (parameter) {
        case 0:
            getDancer(name).grabbedLeft = 1;
            getDancer(name).grabbedRight = 1;
            break;
        case 1:
            getDancer(name).grabbedLeft = 1;
            break;
        case 2:
            getDancer(name).grabbedRight = 1;
            break;
    }
}

void HashTable::info(const std::string& name) const {
    Dancer temp = getDancer(name);
    
    std::cout << temp.leftNeighbour << ' ';
    // Checking leftNeighbour data.
    Dancer left = getDancer(temp.leftNeighbour);
    char relationLeft[5] = {'-','-','-','-'};
    if (temp.grabbedLeft)
        relationLeft[0] = '<';
    if (left.grabbedRight)
        relationLeft[3] = '>';
    relationLeft[4] = '\0';
    std::cout << relationLeft << ' ';
    
    std::cout << name << ' ';
    
    // Checking rightNeighbour data.
    Dancer right = getDancer(temp.rightNeighbour);
    char relationRight[5] = {'-','-','-','-'};
    if (right.grabbedLeft)
        relationRight[0] = '<';
    if (temp.grabbedRight)
        relationRight[3] = '>';
    relationRight[4] = '\0';
    std::cout << relationRight << ' ';
    std::cout << temp.rightNeighbour << '\n';
}

void HashTable::add(const std::string& name, const std::string& leftPerson, const std::string& rightPerson, unsigned countOfDancers) {
    Dancer left = getDancer(leftPerson);
    // Checking if leftPerson and rightPerson are neighbours.
    if (left.rightNeighbour == rightPerson) {
    // Data temp = Data(name, leftPerson, rightPerson);
        insertDancer(name);
        // Editing newDancer's data
        getDancer(name).leftNeighbour = leftPerson;
        getDancer(name).rightNeighbour = rightPerson;
        
        //Editing newDancer's neighbours data
        getDancer(leftPerson).rightNeighbour = name;
        getDancer(leftPerson).grabbedRight = true;
        getDancer(rightPerson).leftNeighbour = name;
        getDancer(rightPerson).grabbedLeft = true;
        
        countOfDancers++;
    }
    else {
        std::cout << leftPerson << " and " << rightPerson << " are not neighbours.\n";
    }
}

void HashTable::remove(const std::string& name, unsigned countOfDancers, std::string& leader) {
    Dancer temp = getDancer(name);
    Dancer left = getDancer(temp.leftNeighbour);
    Dancer right = getDancer(temp.rightNeighbour);
    if (temp.grabbedLeft == 0 && temp.grabbedRight == 0 && left.grabbedRight == 0 && right.grabbedRight == 0) {
        // Updating the leader of the dance if necessary.
        if (temp.name == leader) {
            leader = temp.leftNeighbour;
        }
        // Updating leaving person's neighbour's data.
        left.rightNeighbour = right.name;
        right.leftNeighbour = left.name;
        std::cout << "Free at last!\n";
        countOfDancers--;
        if (countOfDancers <= 2) {
            std::cout << "...and the music stops!\n";
            return;
        }
        return;
    }
    std::cout << "This won't be so easy!\n";
}

void HashTable::swap(const std::string& name1, const std::string& name2) {
    Dancer person1 = getDancer(name1);
    Dancer person2 = getDancer(name2);
    if (person1.rightNeighbour == name2) {
        Dancer person3Left = getDancer(person1.leftNeighbour);
        Dancer person4Right = getDancer(person2.rightNeighbour);
        if (!person1.grabbedLeft && !person2.grabbedRight && !person3Left.grabbedRight && !person4Right.grabbedLeft) {
            // Update Person1's data
            Dancer temp1 = person1;
            person1.leftNeighbour = name2;
            person1.rightNeighbour = person2.rightNeighbour;
            person1.grabbedLeft = temp1.grabbedRight;
            person1.grabbedRight = false;
            // Update Person2's data
            Dancer temp2 = person2;
            person2.rightNeighbour = name1;
            person2.leftNeighbour = temp1.leftNeighbour;
            person2.grabbedRight = temp2.grabbedLeft;
            person2.grabbedLeft = false;
        }
    }
    else if (person1.leftNeighbour == name2) {
        Dancer person3Left = getDancer(person2.leftNeighbour);
        Dancer person4Right = getDancer(person1.rightNeighbour);
        if (!person1.grabbedRight && !person2.grabbedLeft && !person4Right.grabbedLeft && !person3Left.grabbedRight) {
            // Update Person1's data
            Dancer temp1 = person1;
            person1.leftNeighbour = person2.leftNeighbour;
            person1.rightNeighbour = name2;
            person1.grabbedLeft = false;
            person1.grabbedRight = temp1.grabbedLeft;
            // Update Person2's data
            Dancer temp2 = person2;
            person2.leftNeighbour = person1.name;
            person2.rightNeighbour = temp1.rightNeighbour;
            person2.grabbedRight = false;
            person2.grabbedLeft = temp2.grabbedRight;
        }
    }
}

void HashTable::addFromFile(const std::string& name, const std::string& leftPerson, const std::string& rightPerson, unsigned countOfDancers) {
    insertDancer(name);
    // Editing newDancer's data
    getDancer(name).leftNeighbour = leftPerson;
    getDancer(name).rightNeighbour = rightPerson;
    
    countOfDancers++;
}
