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

void HashTable::removeFromList(const std::string& name, unsigned& countOfDancers) {
     unsigned long index = hashFunction(name, chainDance.size());
    chainDance[index].remove(getDancer(name));
    --countOfDancers;
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

void HashTable::grabOrRelease(const std::string& name, unsigned parameter, bool flag) {
    // Using 0 to grab or release both neighbours, 1 to grab or release the left neighbour and 2 to grab or release the right neighbour.
    
    switch (parameter) {
        case 0:
            getDancer(name).grabbedLeft = flag;
            getDancer(name).grabbedRight = flag;
            break;
        case 1:
            getDancer(name).grabbedLeft = flag;
            break;
        case 2:
            getDancer(name).grabbedRight = flag;
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

void HashTable::add(const std::string& newDancerName, const std::string& leftDancer, const std::string& rightDancer, unsigned& countOfDancers) {
    Dancer& dancer1 = getDancer(leftDancer);
    Dancer& dancer2 = getDancer(rightDancer);
    // Checking if leftPerson and rightPerson are neighbours.
    if (dancer1.rightNeighbour == rightDancer) {
        insertDancer(newDancerName);
        Dancer& newDancer = getDancer(newDancerName);
        // Editing newDancer's data
        newDancer.leftNeighbour = leftDancer;
        newDancer.rightNeighbour = rightDancer;
        
        //Editing newDancer's neighbours data
        dancer1.rightNeighbour = newDancerName;
        dancer1.grabbedRight = true;
        dancer2.leftNeighbour = newDancerName;
        dancer2.grabbedLeft = true;
        
        ++countOfDancers;
    }
    else {
        std::cout << leftDancer << " and " << rightDancer << " are not neighbours\n";
    }
}

void HashTable::remove(const std::string& name, unsigned& countOfDancers, std::string& leader, bool& enoughDancers) {
    Dancer& temp = getDancer(name);
    Dancer& left = getDancer(temp.leftNeighbour);
    Dancer& right = getDancer(temp.rightNeighbour);
    if (temp.grabbedLeft == false && temp.grabbedRight == false && left.grabbedRight == false && right.grabbedLeft == false) {
        // Updating the leader of the dance if necessary.
        if (temp.name == leader) {
            leader = temp.leftNeighbour;
        }
        // Updating leaving person's neighbour's data.
        left.rightNeighbour = right.name;
        right.leftNeighbour = left.name;
        std::cout << "Free at last!\n";
        removeFromList(temp.name, countOfDancers);
        if (countOfDancers <= 2) {
            std::cout << "...and the music stops!\n";
            enoughDancers = false;
            return;
        }
        return;
    }
    std::cout << "This won't be so easy!\n";
}

void HashTable::swap(const std::string& dancer1Name, const std::string& dancer2Name, std::string& leader) {
    Dancer& dancer1 = getDancer(dancer1Name);
    Dancer& dancer2 = getDancer(dancer2Name);
    if (dancer1.rightNeighbour == dancer2Name) {
        Dancer& dancer1Left = getDancer(dancer1.leftNeighbour);
        Dancer& dancer2Right = getDancer(dancer2.rightNeighbour);
        if (!dancer1.grabbedLeft && !dancer2.grabbedRight && !dancer1Left.grabbedRight && !dancer2Right.grabbedLeft) {
            // Update dancer1's data
            dancer1.leftNeighbour = dancer2Name;
            dancer1.rightNeighbour = dancer2Right.name;
            dancer1.grabbedLeft = dancer1.grabbedRight;
            dancer1.grabbedRight = false;
            dancer2Right.leftNeighbour = dancer1.name;
            // Update dancer2's data
            dancer2.rightNeighbour = dancer1Name;
            dancer2.leftNeighbour = dancer1Left.name;
            dancer2.grabbedRight = dancer2.grabbedLeft;
            dancer2.grabbedLeft = false;
            dancer1Left.rightNeighbour = dancer2.name;
            if (dancer1Name == leader) {
                leader = dancer2Name;
                return;
            }
            if (dancer1Name == leader)
                leader = dancer1Name;
        }
    }
    else if (dancer1.leftNeighbour == dancer2Name) {
        Dancer& dancer2Left = getDancer(dancer2.leftNeighbour);
        Dancer& dancer1Right = getDancer(dancer1.rightNeighbour);
        if (!dancer1.grabbedRight && !dancer2.grabbedLeft && !dancer1Right.grabbedLeft && !dancer2Left.grabbedRight) {
            // Update dancer's data
            dancer1.rightNeighbour = dancer2Name;
            dancer1.leftNeighbour = dancer2Left.name;
            dancer1.grabbedRight = dancer1.grabbedLeft;
            dancer1.grabbedLeft = false;
            dancer2Left.rightNeighbour = dancer1.name;
            // Update dancer2's data
            dancer2.leftNeighbour = dancer1.name;
            dancer2.rightNeighbour = dancer1Right.name;
            dancer2.grabbedLeft = dancer2.grabbedRight;
            dancer2.grabbedRight = false;
            dancer1Right.leftNeighbour = dancer2.name;
            if (dancer1Name == leader) {
                leader = dancer2Name;
                return;
            }
            if (dancer2Name == leader)
                leader = dancer1Name;
        }
    }
}

void HashTable::addFromFile(const std::string& name, const std::string& leftPerson, const std::string& rightPerson, unsigned& countOfDancers) {
    insertDancer(name);
    // Editing newDancer's data
    getDancer(name).leftNeighbour = leftPerson;
    getDancer(name).rightNeighbour = rightPerson;
    ++countOfDancers;
}
