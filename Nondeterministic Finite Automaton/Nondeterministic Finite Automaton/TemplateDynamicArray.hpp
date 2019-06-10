//
//  TemplateDynamicArray.hpp
//  Nondeterministic Finite Automaton
//

#ifndef DynamicArray_hpp
#define DynamicArray_hpp
#include <iostream>


const unsigned short STARTING_CAPACITY = 2;

template <typename T>
class DynamicArray
{
public:
    DynamicArray();
    DynamicArray(const DynamicArray<T>&);
    DynamicArray& operator=(const DynamicArray&);
    const T& operator[](unsigned) const;
    T& operator[](unsigned);
    bool operator==(const DynamicArray<T>&) const;
    ~DynamicArray();
    
public:
    void addElement(const T&);
    void removeElement(const T&);
    int findElementIndex(const T&) const;
    unsigned getSize() const;
    
private:
    void free();
    void resize();
    void copy(const DynamicArray<T>&);
    int linearSearch(const T&) const;
    
private:
    T* dynamicArray;
    unsigned size;
    unsigned capacity;
};

template <typename T>
DynamicArray<T>::DynamicArray()
{
    try {
        dynamicArray = new T[STARTING_CAPACITY];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Bad alloc caught: " << ba.what() << '\n';
        throw;
    }
    capacity = STARTING_CAPACITY;
    size = 0;
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& newdynamicArray)
{
    copy(newdynamicArray);
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& newdynamicArray)
{
    if (this != &newdynamicArray)
    {
        free();
        copy(newdynamicArray);
    }
    return *this;
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
    free();
}

template <typename T>
void DynamicArray<T>::resize()
{
    T* temp = nullptr;
    try {
        temp = new T[capacity * STARTING_CAPACITY];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Bad alloc caught: " << ba.what() << '\n';
        throw;
    }
    
    capacity *= STARTING_CAPACITY;
    
    for (unsigned i = 0; i < size; ++i)
    {
        temp[i] = dynamicArray[i];
    }
    
    delete[] dynamicArray;
    dynamicArray = temp;
}

template <typename T>
void DynamicArray<T>::free()
{
    delete[] dynamicArray;
}

template <typename T>
void DynamicArray<T>::copy(const DynamicArray<T>& rhs)
{
    try {
        dynamicArray = new T[rhs.size];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Bad alloc caught: " << ba.what() << '\n';
        throw;
    }
    
    for (size_t i = 0; i < rhs.size; ++i)
    {
        dynamicArray[i] = rhs.dynamicArray[i];
    }
    capacity = rhs.capacity;
    size = rhs.size;
}

template <typename T>
void DynamicArray<T>::addElement(const T& element)
{
    if (size == capacity)
    {
        resize();
    }
    dynamicArray[size] = element;
    size++;
}

template <typename T>
void DynamicArray<T>::removeElement(const T& element)
{
    int index = findElementIndex(element);
    if(index == -1)
    {
        std::cout << "There is no such element\n";
        return;
    }
    for(size_t i = index; index < size-1; ++i)
    {
        dynamicArray[i] = dynamicArray[i+1];
    }
    size--;
}

template <typename T>
int DynamicArray<T>::findElementIndex(const T& element) const
{
    return  linearSearch(element);
}

template <typename T>
int DynamicArray<T>::linearSearch(const T& element) const
{
    for(unsigned i = 0; i < size; ++i)
    {
        if(this->dynamicArray[i] == element)
        {
            return i;
        }
    }
    return -1;
}

template <typename T>
const T& DynamicArray<T>::operator[](unsigned index) const
{
   
    try {
        if (index < 0 || index > size - 1)
            throw std::invalid_argument("Invalid index");
    } catch (const std::invalid_argument& excp) {
        std::cerr << "Exception caught: " << excp.what() << '\n';
        throw;
    }
    return dynamicArray[index];
}

template <typename T>
T& DynamicArray<T>::operator[](unsigned index)
{
    try {
        if (index < 0 || index > size - 1)
            throw std::invalid_argument("Invalid index");
    } catch (const std::invalid_argument& excp) {
        std::cerr << "Exception caught: " << excp.what() << '\n';
        throw;
    }
    return dynamicArray[index];
}

template <typename T>
unsigned DynamicArray<T>::getSize() const
{
    return size;
}

template <typename T>
bool DynamicArray<T>::operator==(const DynamicArray<T>& rhs) const
{
    // Operator logic designed by Peter Badjakov.
    if (this->size != rhs.size)
    {
        return false;
    }
    if (this->dynamicArray == rhs.dynamicArray)
    {
        return true;
    }
    for (unsigned i = 0; i < this->size; ++i)
    {
        if (!(this->dynamicArray[i] == rhs.dynamicArray[i]))
        {
            return false;
        }
    }
    return true;
}

#endif
