//  Code ran and tested on Clang (Xcode Version 10.1)
//
//  Vector.cpp
//  Conga
//

const unsigned short STARTING_CAPACITY = 2;

#include "Vector.hpp"
#include <iostream>

Vector::Vector()
{
    try {
        arr = new LinkedList*[STARTING_CAPACITY];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Cannot allocate memory for a new vector.\n";
        throw;
    }
    size = 0;
    capacity = STARTING_CAPACITY;
}

//    Copy constructor and operator= are presented just to show the data structure Vector. In the program only one vector is needed, so theese two are added as comments.

//Vector::Vector(const Vector& newVector)
//{
//    copy(newVector);
//}
//
//Vector& Vector::operator=(const Vector& newVector)
//{
//    if(this != &newVector)
//    {
//        clear();
//        copy(newVector);
//    }
//    return *this;
//}

Vector::~Vector()
{
    clear();
}

void Vector::clear()
{
    for(unsigned i = 0; i < size; ++i)
    {
        delete arr[i];
    }
}

void Vector::resize()
{
    LinkedList** temp = nullptr;
    try {
        temp = new LinkedList*[capacity*STARTING_CAPACITY];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Cannot allocate memory for a new vector.\n";
        throw;
    }
    
    for(unsigned i = 0; i < size; ++i)
    {
        temp[i] = arr[i];
    }
    delete[] arr;
    arr = temp;
    temp = nullptr;
    capacity *= STARTING_CAPACITY;
}

void Vector::copy(const Vector& newVector)
{
    try {
        arr = new LinkedList*[newVector.capacity];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Cannot allocate memory for a new vector.\n";
        throw;
    }
    
    for(unsigned i = 0; i < newVector.size; ++i)
    {
        arr[i] = newVector.arr[i];
    }
    size = newVector.size;
    capacity = newVector.capacity;
}

void Vector::updateArray(unsigned lineIndex) // When a chain is deleted, this function updates the content of the vector. Swapping is faster (O(1)), but here the order of the chains is a priority, so the complexity is O(n).
{
    if(lineIndex >= size)
    {
        std::cerr << "Wrong input\n";
        return;
    }
    
    for(unsigned i = lineIndex; i < size - 1; ++i)
    {
        arr[i] = arr[i+1];
    }
    arr[size-1] = nullptr;
    size--;
}

void Vector::addConga(LinkedList* conga)
{
    if(size == capacity)
    {
        resize();
    }
    arr[size] = conga;
    size++;
}

void Vector::removeByNameVector(const char* newName, unsigned lineIndex)
{
    if(lineIndex >= size)
    {
        std::cerr << "Wrong input\n";
        return;
    }
    short newChainFlag = 0; // This flag is used to control wether a new chain is constructed or the current one has been deleted so the array have to be updated.
    LinkedList* eventualNewChain = arr[lineIndex]->removeByNameNode(newName, newChainFlag);
    switch (newChainFlag) {
        case 1: // If the current chain is deleted the array will be updated.
            updateArray(lineIndex);
            break;
        case 2: // If a new chain is constructed it will be added to the vector.
            addConga(eventualNewChain);
            break;
        case 3: // If the chain is longer than 1, after popFront or popBack it is returned.
            return;
            break;
    }
}

void Vector::merge(unsigned lineIndex1, unsigned lineIndex2)
{
    if(lineIndex1 >= size || lineIndex2 >= size || lineIndex1 == lineIndex2)
    {
        std::cerr << "Wrong input\n";
        return;
    }
    bool mergeIsSuccessful = false; // This flag is used to control wether the merger of the two chains is successful and if it is, the vector will be updated.
    arr[lineIndex1]->mergeLists(arr[lineIndex2], mergeIsSuccessful);
    if(mergeIsSuccessful)
    {
        updateArray(lineIndex2);
    }
}

void Vector::printVector() const
{
    for(unsigned i = 0; i < size; ++i)
    {
        std::cout << "Line" << i << ": ";
        arr[i]->printList();
        std::cout << std::endl;
    }
}

void Vector::append(const char* newName, University newUniversity, unsigned lineIndex)
{
    if(lineIndex >= size)
    {
        std::cerr << "Wrong input\n";
        return;
    }
    arr[lineIndex]->append(newName, newUniversity);
}

void Vector::removeLast(unsigned lineIndex)
{
    if(lineIndex >= size)
    {
        std::cerr << "Wrong input\n";
        return;
    }
    if(arr[lineIndex]->getSize() != 1)
    {
        arr[lineIndex]->popBack();
    }
    else // If the node is only one, after deleting it the vector is updated so there is no gap in it.
    {
        arr[lineIndex]->popBack();
        updateArray(lineIndex);
    }
}

void Vector::removeFirst(unsigned lineIndex)
{
    if(lineIndex >= size)
    {
        std::cerr << "Wrong input\n";
        return;
    }
    if(arr[lineIndex]->getSize() != 1)
    {
        arr[lineIndex]->popFront();
    }
    else // If the node is only one, after deleting it I update the vector so there is no gap in it.
    {
        arr[lineIndex]->popFront();
        updateArray(lineIndex);
    }
}

