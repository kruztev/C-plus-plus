//
//  Dynamic Array.cpp
//  OOP Practices
//


#include "Dynamic Array.h"

const unsigned short STARTING_CAPACITY = 2;

DynamicArray::DynamicArray()
{
    try {
        arr = new Clock[STARTING_CAPACITY];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Cannot allocate memory for a new dynamic array\n";
        throw;
    }
    size = 0;
    capacity = STARTING_CAPACITY;
}

DynamicArray::DynamicArray(const DynamicArray& rhs)
{
    copy(rhs);
}

DynamicArray& DynamicArray::operator=(const DynamicArray& rhs)
{
    if(this != &rhs)
    {
        clear();
        copy(rhs);
    }
    return *this;
}

DynamicArray::~DynamicArray()
{
    clear();
}

void DynamicArray::addClock(const Clock& rhs)
{
    if (size == capacity)
    {
        resize();
    }
    arr[size] = rhs;
    size++;
}

void DynamicArray::removeClock()
{
    size--;
}

void DynamicArray::resize()
{
    Clock* temp = nullptr;
    try {
        temp = new Clock[capacity*STARTING_CAPACITY];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Cannot allocate memory to resize\n";
        throw;
    }
    capacity *= STARTING_CAPACITY;
    for(size_t i = 0; i < size; ++i)
    {
        temp[i] = arr[i];
    }
    delete[] arr;
    arr = temp;
    temp = nullptr;
}


void DynamicArray::copy(const DynamicArray& rhs)
{
    arr = nullptr;
    try {
        arr = new Clock[rhs.capacity];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Cannot allocate memory to copy\n";
        throw;
    }
    capacity *= STARTING_CAPACITY;
    for(size_t i = 0; i < size; ++i)
    {
        arr[i] = rhs.arr[i];
    }
    size = rhs.size;
    capacity = rhs.capacity;
}

void DynamicArray::clear()
{
    delete[] arr;
}
