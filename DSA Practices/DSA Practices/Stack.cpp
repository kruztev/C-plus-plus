//
//  Stack.cpp
//  SDP Practs
//


#include "Stack.hpp"
#include <iostream>
unsigned short const STARTING_CAPACITY = 2;

template <typename T>
Stack<T>::Stack()
{
    try {
        arr = new T[STARTING_CAPACITY];
        size = 0;
        capacity = STARTING_CAPACITY;
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Cannot allocate memory for a new stack.\n";
        throw;
    }
    
}

template <typename T>
Stack<T>::Stack(const Stack& newStack)
{
    copy(newStack);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& newStack)
{
    if(this != &newStack)
    {
        clear();
        copy(newStack);
    }
    return *this;
}

template <typename T>
Stack<T>::~Stack()
{
    clear();
}

template <typename T>
void Stack<T>::copy(const Stack& newStack)
{
    T* temp = nullptr;
    try {
        temp = new T[newStack.capacity];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Cannot allocate memory for a new stack.\n";
        throw;
    }
    for(unsigned i = 0; i < newStack.size; ++i)
    {
        temp[i] = newStack.arr[i];
    }
    arr = temp;
    temp = nullptr;
}

template <typename T>
void Stack<T>::clear()
{
    delete[] arr;
}

template <typename T>
void Stack<T>::resize()
{
    T* temp;
    try {
        temp = new T[capacity*STARTING_CAPACITY];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Cannot allocate memory for a new stack.\n";
        throw;
    }
    for(unsigned i = 0; i < size; ++i)
    {
        temp[i] = arr[i];
    }
    
    clear();
    arr = temp;
    temp = nullptr;
    capacity *= STARTING_CAPACITY;
    
}

template <typename T>
bool Stack<T>::isEmpty()
{
    if(size == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
T Stack<T>::peak()
{
    return arr[size-1];
}

template <typename T>
void Stack<T>::push(const T element)
{
    if(size == capacity)
    {
        resize();
    }
    arr[size] = element;
    size++;
}

template <typename T>
T Stack<T>::pop()
{
    return arr[size-1];
    size--;
}


bool isCorrect(char* str, unsigned len)
{
    Stack<char> stack;
    for(unsigned i = 0; i < len; ++i)
    {
        if(str[i] == '(' || str[i] == '[' || str[i] == '{')
            stack.push(str[i]);
        if((stack.peak() == str[i] && str[i] == ')') ||
           (stack.peak() == str[i] && str[i] == ']') ||
           (stack.peak() == str[i] && str[i] == '}'))
            stack.pop();
    }
    if(stack.isEmpty())
        return true;
    return false;
}

