//
//  LinkedList.hpp
//  SDP Practs
//

#pragma once

template <typename T>
class LinkedList
{
public:
    LinkedList();
    LinkedList(const LinkedList&);
    LinkedList& operator=(const LinkedList&);
    ~LinkedList();
    
private:
    class Node
    {
    public:
        T data;
        Node* next;
        
        Node(const T& newData, Node* newPtr = nullptr) :
        data(newData), next(newPtr)
        {}
    };
    
    Node* frontPtr;
    Node* backPtr;
    unsigned size;
    
public:
    void pushFront(const T&);
    void popFront();
    void pushBack(const T&);
    void popBack();
    const T& backElement() const;
    T& backElement();
    const T& frontElement() const;
    T& frontElement();
    bool isEmpty() const;
    unsigned getSize() const;
    void insertAt(const T&, const Node*);
    void removeAt(const Node*);
    LinkedList& sortByParity();
    
    
private:
    void clear();
    void copy(const LinkedList&);
    
public:
    class Iterator
    {
        //friend class LinkedList;
    public:
        Iterator(Node* nPtr): ptr(nPtr) {};
        Iterator& operator=(const Iterator&);
        Iterator& operator++();
        Iterator& operator--();
        T& operator*();
        const T& operator*() const;
        T& operator->();
        bool operator!=(const Node&);
        
    private:
        Node* ptr;
        
    };
public:
    Iterator begin();
    Iterator end();
    
};

template <typename T>
LinkedList<T>::LinkedList() :
frontPtr(nullptr), backPtr(nullptr), size(0)
{}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& newList)
{
    copy(newList);
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& newList)
{
    if(*this != newList)
    {
        clear();
        copy(newList);
    }
    return *this;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    clear();
}

template <typename T>
void LinkedList<T>::clear()
{
    Node* destroyer;
    
    while(frontPtr != nullptr)
    {
        destroyer = frontPtr;
        frontPtr = frontPtr -> next;
        delete destroyer;
    }
    
    frontPtr = nullptr;
    backPtr = nullptr;
    size = 0;
}

template <typename T>
void LinkedList<T>::copy(const LinkedList& newList)
{
    if(newList.isEmpty())
    {
        return;
    }
    
    try
    {
        frontPtr = new Node(newList.frontPtr->data);
        Node* temp = frontPtr;
        Node* copyFrom = newList.frontPtr;
        
        while(copyFrom->next != nullptr)
        {
            copyFrom = copyFrom->next;
            temp->next = new Node(copyFrom->data);
            temp = temp->next;
        }
        
        backPtr = copyFrom;
    }
        catch (const std::bad_alloc& ba) {
        std::cerr << "Cannot allocate memory to copy linked list.\n";
        clear();
        throw;
    }
    
}

template <typename T>
void LinkedList<T>::pushFront(const T& newNode)
{
    try {
        if(isEmpty())
        {
            frontPtr = new Node(newNode);
            backPtr = frontPtr;
            size++;
            return;
        }
        
        Node* newElement = new Node(newNode);
        newElement->next = frontPtr;
        frontPtr = newElement;
        size++;
    }
    catch (const std::bad_alloc& ba)
    {
        std::cerr << "Cannot allocate memory to push fornt.\n";
        throw;
    }
    
}

template <typename T>
void LinkedList<T>::pushBack(const T& newNode)
{
    if(isEmpty())
    {
        pushFront(newNode);
        return;
    }
    try {
        backPtr->next = new Node(newNode);
        backPtr = backPtr->next;
        size++;
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Cannot allocate memory to push back.\n";
        throw;
    }
}

template <typename T>
void LinkedList<T>::popFront()
{
    if(isEmpty())
    {
        return;
    }
    Node* temp = frontPtr;
    frontPtr = frontPtr->next;
    delete temp;
    size--;
}

template <typename T>
void LinkedList<T>::popBack()
{
    if(isEmpty())
    {
        return;
    }
    
    if(size == 1)
    {
        delete frontPtr;
        frontPtr = nullptr;
        backPtr = nullptr;
        size = 0;
    }
    
    while(frontPtr->next->next != nullptr)
    {
        frontPtr = frontPtr->next;
    }
    delete frontPtr->next->next;
    backPtr = frontPtr->next;
    backPtr->next = nullptr;
    size--;
}

template <typename T>
const T& LinkedList<T>::backElement() const
{
    if(isEmpty())
    {
        throw std::logic_error("The list is empty.\n");
    }
    return backPtr->data;
}

template <typename T>
T& LinkedList<T>::backElement()
{
    if(isEmpty())
    {
        throw std::logic_error("The list is empty.\n");
    }
    return backPtr->data;
}

template <typename T>
const T& LinkedList<T>::frontElement() const
{
    if(isEmpty())
    {
        throw std::logic_error("The list is empty.\n");
    }
    return frontPtr->data;
}

template <typename T>
T& LinkedList<T>::frontElement()
{
    if(isEmpty())
    {
        throw std::logic_error("The list is empty.\n");
    }
    return frontPtr->data;
}

template <typename T>
bool LinkedList<T>::isEmpty() const
{
    return (size != 0) ? 1 : 0;
}

template <typename T>
unsigned LinkedList<T>::getSize() const
{
    return size;
}

template <typename T>
void LinkedList<T>::insertAt(const T& newElementData, const Node* previousElement)
{
    Node* newNode = nullptr;
    try
    {
        Node* newNode = new Node(newElementData);
    }
    catch (const std::bad_alloc& ba)
    {
        std::cerr << "Cannot allocate memory for a new node.\n";
        throw;
    }
    
    Node* temp = nullptr;
    temp = previousElement->next;
    previousElement->next = newNode;
    newNode->next = temp;
    size++;
}

template <typename T>
void LinkedList<T>::removeAt(const Node* previousElement)
{
    Node* temp = nullptr;
    temp = previousElement->next->next;
    delete previousElement->next;
    previousElement->next = temp;
    size--;
}

template <typename T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator=(const Iterator& it)
{
    return ptr = it.ptr;
}

template <typename T>
T& LinkedList<T>::Iterator::operator*()
{
    return ptr->data;
}

template <typename T>
const T& LinkedList<T>::Iterator::operator*() const
{
    return ptr->data;
}

template <typename T>
T& LinkedList<T>::Iterator::operator->()
{
    return &ptr->data;
}

template <typename T>
bool LinkedList<T>::Iterator::operator!=(const Node& rhs)
{
    return !(rhs == *this);
}

template <typename T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++()
{
    ptr = ptr->next;
    return *this;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin()
{
    return Iterator(frontPtr);
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end()
{
    return Iterator(backPtr);
}
