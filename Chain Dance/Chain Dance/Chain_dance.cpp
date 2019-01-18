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

unsigned HashTable::hashFunction(const std::string& key, unsigned int size)
{
    unsigned result = key.size();
    unsigned limit = result;
    for(unsigned i = 0; i < limit; ++i)
    {
        result += (unsigned)key[i];
    }
    return result % size;
}

void HashTable::insertElement(const std::string& name)
{
    unsigned index = hashFunction(name, chainDance.size());
    for(iterator t = chainDance[index].begin(); t != chainDance[index].end(); ++t)
    {
        if(t.operator*().name == name)
        {
            std::cout << "This person has already been added to the chain dance.\n";
            return;
        }
    }
    if(chainDance[index].size() >= MAX_CHAIN_SIZE)
    {
        rehash();
        index = hashFunction(name, chainDance.size());
    }
    Data data = Data(name);
    chainDance[index].push_front(data);
}

void HashTable::rehash()
{
    table temp(chainDance.capacity()*2);
    for(unsigned index = 0; index < chainDance.size(); ++index)
    {
        if(!chainDance[index].empty())
        {
            for(iterator t = chainDance[index].begin(); t != chainDance[index].end(); ++t)
            {
                unsigned newIndex = hashFunction((*t).name, temp.size());
                temp[newIndex].push_front(*t);
            }
        }
    }
    chainDance = temp;
}

HashTable::Data& HashTable::getElement(const std::string& name)
{
    unsigned index = hashFunction(name, chainDance.size());
    if(chainDance[index].empty())
    {
        throw std::logic_error("No person named like that.\n");
    }
    else if(name == chainDance[index].front().name)
    {
        return chainDance[index].front();
    }
    else
    {
        for(iterator t = ++chainDance[index].begin(); t != chainDance[index].end(); ++t)
        {
            if(name == (*t).name)
            {
                return *t;
            }
        }
    }
    throw std::logic_error("No person named like that.\n");
}

void HashTable::removeElement(const std::string& name)
{
     unsigned index = hashFunction(name, chainDance.size());
    chainDance[index].remove(getElement(name));
}

void HashTable::print(std::string leader)
{
    std::cout << leader << '\n';
    std::string temp = getElement(leader).leftNeighbour;
    while (temp != leader)
    {
        std::cout << temp << '\n';
        temp = getElement(temp).leftNeighbour;
    }
}

bool HashTable::Data::operator==(const Data& nData) const
{
   return (this->name == nData.name) ? true : false;
}

void HashTable::release(const std::string name, unsigned parameter)
{
// Using 0 to release both neighbours, 1 to release the left neighbour and 2 to release the right neighbour.
    switch (parameter) {
        case 0:
            getElement(name).grabbedLeft = 0;
            getElement(name).grabbedRight = 0;
            break;
        case 1:
            getElement(name).grabbedLeft = 0;
            break;
        case 2:
            getElement(name).grabbedRight = 0;
            break;
    }
}

void HashTable::grab(const std::string name, unsigned parameter)
{
    // Using 0 to grab both neighbours, 1 to grab the left neighbour and 2 to grab the right neighbour.
    switch (parameter) {
        case 0:
            getElement(name).grabbedLeft = 1;
            getElement(name).grabbedRight = 1;
            break;
        case 1:
            getElement(name).grabbedLeft = 1;
            break;
        case 2:
            getElement(name).grabbedRight = 1;
            break;
    }
}

void HashTable::info(std::string name)
{
    Data temp = getElement(name);
    
    std::cout << temp.leftNeighbour << ' ';
    // Checking leftNeighbour data.
    Data left = getElement(temp.leftNeighbour);
    char relationLeft[4] = {'-','-','-','-'};
    if(temp.grabbedLeft)
        relationLeft[0] = '<';
    if(left.grabbedRight)
        relationLeft[3] = '>';
    std::cout << relationLeft << ' ';
    
    std::cout << name << ' ';
    
    // Checking rightNeighbour data.
    Data right = getElement(temp.rightNeighbour);
    char relationRight[4] = {'-','-','-','-'};
    if(right.grabbedLeft)
        relationRight[0] = '<';
    if(temp.grabbedRight)
        relationRight[3] = '>';
    std::cout << relationRight << ' ';
    std::cout << temp.rightNeighbour;
}

void HashTable::add(const std::string& name, const std::string& leftPerson, const std::string& rightPerson, unsigned countOfDancers)
{
    Data left = getElement(leftPerson);
    // Checking if leftPerson and rightPerson are neighbours.
    if(left.rightNeighbour == rightPerson)
    {
    // Data temp = Data(name, leftPerson, rightPerson);
        insertElement(name);
        // Editing newDancer's data
        getElement(name).leftNeighbour = leftPerson;
        getElement(name).rightNeighbour = rightPerson;
        
        //Editing newDancer's neighbours data
        getElement(leftPerson).rightNeighbour = name;
        getElement(leftPerson).grabbedRight = true;
        getElement(rightPerson).leftNeighbour = name;
        getElement(rightPerson).grabbedLeft = true;
        
        countOfDancers++;
    }
    else
    {
        std::cout << leftPerson << " and " << rightPerson << " are not neighbours.\n";
    }
}

void HashTable::remove(const std::string& name, unsigned countOfDancers, std::string& leader)
{
    Data temp = getElement(name);
    Data left = getElement(temp.leftNeighbour);
    Data right = getElement(temp.rightNeighbour);
    if(temp.grabbedLeft == 0 && temp.grabbedRight == 0 && left.grabbedRight == 0 && right.grabbedRight == 0)
    {
        // Updating the leader of the dance if necessary.
        if(temp.name == leader)
        {
            leader = temp.leftNeighbour;
        }
        // Updating leaving person's neighbour's data.
        left.rightNeighbour = right.name;
        right.leftNeighbour = left.name;
        std::cout << "Free at last!\n";
        countOfDancers--;
        if(countOfDancers <= 2)
        {
            std::cout << "...and the music stops!\n";
            return;
        }
        return;
    }
    std::cout << "This won't be so easy!\n";
}

void HashTable::swap(const std::string& name1, const std::string& name2)
{
    Data person1 = getElement(name1);
    Data person2 = getElement(name2);
    if(person1.rightNeighbour == name2)
    {
        Data person3Left = getElement(person1.leftNeighbour);
        Data person4Right = getElement(person2.rightNeighbour);
        if(!person1.grabbedLeft && !person2.grabbedRight && !person3Left.grabbedRight && !person4Right.grabbedLeft)
        {
            // Update Person1's data
            Data temp1 = person1;
            person1.leftNeighbour = name2;
            person1.rightNeighbour = person2.rightNeighbour;
            person1.grabbedLeft = temp1.grabbedRight;
            person1.grabbedRight = false;
            // Update Person2's data
            Data temp2 = person2;
            person2.rightNeighbour = name1;
            person2.leftNeighbour = temp1.leftNeighbour;
            person2.grabbedRight = temp2.grabbedLeft;
            person2.grabbedLeft = false;
        }
    }
    else if(person1.leftNeighbour == name2)
    {
        Data person3Left = getElement(person2.leftNeighbour);
        Data person4Right = getElement(person1.rightNeighbour);
        if(!person1.grabbedRight && !person2.grabbedLeft && !person4Right.grabbedLeft && !person3Left.grabbedRight)
        {
            // Update Person1's data
            Data temp1 = person1;
            person1.leftNeighbour = person2.leftNeighbour;
            person1.rightNeighbour = name2;
            person1.grabbedLeft = false;
            person1.grabbedRight = temp1.grabbedLeft;
            // Update Person2's data
            Data temp2 = person2;
            person2.leftNeighbour = person1.name;
            person2.rightNeighbour = temp1.rightNeighbour;
            person2.grabbedRight = false;
            person2.grabbedLeft = temp2.grabbedRight;
        }
    }
}

void HashTable::addFromFile(const std::string& name, const std::string& leftPerson, const std::string& rightPerson, unsigned countOfDancers)
{
    insertElement(name);
    // Editing newDancer's data
    getElement(name).leftNeighbour = leftPerson;
    getElement(name).rightNeighbour = rightPerson;
    
    countOfDancers++;
}
