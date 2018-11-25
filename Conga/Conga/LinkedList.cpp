//  Code ran and tested on Clang (Xcode Version 10.1)
//
//  LinkedList.cpp
//  Conga
//

#include "LinkedList.hpp"
#include <iostream>

LinkedList::LinkedList()
{
    front = back = new Node();
    size = 0;
}

LinkedList::LinkedList(const char* newName, University newUniversity)
{
    front = back = new Node(newName, newUniversity);
    size = 1;
}

LinkedList::LinkedList(const LinkedList& newList)
{
    copy(newList);
}


// Using this constructor to create nodes by pointer.
LinkedList::LinkedList(Node* pToNewLinkedList)
{
    front = pToNewLinkedList;
    front->previous = nullptr;
    Node* temp = front;
    while(temp->next != nullptr)
    {
        temp = temp->next;
    }
    back = temp;
    back->next = nullptr;
    setSize();
    
}

LinkedList& LinkedList::operator=(const LinkedList& newList)
{
    if(this != &newList)
    {
        clear();
        copy(newList);
    }
    return *this;
}

LinkedList::~LinkedList()
{
    clear();
}

void LinkedList::clear()
{
    Node* destroyer;
    
    while(front != nullptr)
    {
        destroyer = front;
        front = front->next;
        delete destroyer;
    }
    front = nullptr;
    back = nullptr;
    size = 0;
}

LinkedList::Node::Node()
{
    name = new char[2];
    name[0] = name[1] = '\0';
    university = INVALID_UNIVERSITY;
    next = nullptr;
    previous = nullptr;
}

// Node constructor
LinkedList::Node::Node(const char* newName, University newUniversity)
{
    try {
        name = new char[strlen(newName)+1];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Cannot allocate memory to create a new node.\n";
        throw;
    }
    strcpy(name, newName);
    university = newUniversity;
    next = nullptr;
    previous = nullptr;
}

LinkedList::Node::~Node()
{
    delete[] name;
}

void LinkedList::copy(const LinkedList& newList)
{
    try {
        front = new Node(newList.front->name, newList.front->university);
        //copyData(front, newList.front);
        Node*copyFrom = newList.front->next;
        Node*temp = front->next; // I'm using this pointer to keep current position in the new chain.
        Node* tempPrevious = front;
        while(copyFrom != nullptr)
        {
            temp = new Node(copyFrom->name, copyFrom->university);
            temp->previous = tempPrevious;
            tempPrevious = temp;
            temp = temp->next;
            copyFrom = copyFrom->next;
        }
        back = tempPrevious;
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Cannot allocate memory for a new node.\n";
        throw;
    }
    size = newList.size;
}

void LinkedList::pushBack(const char* name, University university)
{
    Node* newNode = new Node(name, university);
    if(size == 0)
    {
        front = back = newNode;
        newNode->previous = nullptr;
        newNode->next = nullptr;
    }
    else
    {
        back->next = newNode;
        newNode->previous = back;
        newNode->next = nullptr;
        back = newNode;
    }
    size++;
}

void LinkedList::popBack()
{
    if(size == 1)
    {
        clear();
        return;
    }
    Node*temp = back->previous;
    delete back;
    back = temp;
    back->next = nullptr;
    back->previous = temp->previous;
    size--;
}

void LinkedList::popFront()
{
    if(size == 1)
    {
        clear();
        return;
    }
    Node*temp = front->next;
    delete front;
    front = temp;
    front->next = temp->next;
    front->previous = nullptr;
    size--;
}

unsigned LinkedList::getSize() const
{
    return size;
}

// Compare by name function
bool cmpByName(const char* name1, const char* name2)
{
    unsigned long len1 = strlen(name1);
    unsigned long len2 = strlen(name2);
    if(len1 != len2)
    {
        return false;
    }
    
    for(unsigned i = 0; i < len1; ++i)
    {
        if(name1[i] != name2[i])
        {
            return false;
        }
    }
    return true;
}

void LinkedList::setSize()
{
    unsigned cnt = 0;
    Node* temp = front;
    while(temp != back)
    {
        cnt++;
        temp = temp->next;
    }
    cnt++;
    size = cnt;
}

LinkedList* LinkedList::removeByNameNode(const char* exampleName, short &newChainFlag)
{
    if(cmpByName(exampleName, front->name))
    {
        popFront();
        if(size == 0)
        {
            LinkedList* emptyLinkedList = new LinkedList();
            newChainFlag = 1;
            return emptyLinkedList;
        }
        newChainFlag = 3;
        return this;
    }
    else
    {
        Node* temp = front->next;
        while(temp != back)
        {
            if(cmpByName(exampleName, temp->name))
            {
                LinkedList* newLinkedList = new LinkedList(temp->next); // Saving the rest of the chain in a new linked list.
                back = temp->previous;
                delete temp;
                back->next = nullptr;
                setSize();
                newChainFlag = 2; // Indicating that the function will return a new chain.
                return newLinkedList;
            }
            temp = temp->next;
        }
        
        if (cmpByName(exampleName, back->name))
        {
            popBack();
            if(size == 0)
            {
                LinkedList* emptyLinkedList = new LinkedList();
                newChainFlag = 1;
                return emptyLinkedList;
            }
            newChainFlag = 3;
            return this;
        }
        
        std::cout << "There is no person named " << exampleName << std::endl;
        LinkedList* emptyLinkedList = new LinkedList();
        return emptyLinkedList;
    }
}

void LinkedList::mergeLists(LinkedList* pToConga, bool& mergeIsSuccessful)
{
    switch (pToConga->front->university) {
        case FMI:
            if(this->back->university == UNSS)
            {
                std::cout << "Incompatible people\n";
                return;
            }
            else
            {
                this->back->next = pToConga->front;
                pToConga->front->previous = this->back;
                this->back = pToConga->back;
                pToConga->front = nullptr;
                mergeIsSuccessful = true;
            }
            break;
        case TU:
            if(this->back->university == FMI)
            {
                std::cout << "Incompatible people\n";
                return;
            }
            else
            {
                this->back->next = pToConga->front;
                pToConga->front->previous = this->back;
                this->back = pToConga->back;
                pToConga->front = nullptr;
                mergeIsSuccessful = true;
            }
            break;
        case UNSS:
            if(this->back->university == TU)
            {
                std::cout << "Incompatible people\n";
                return;
            }
            else
            {
                this->back->next = pToConga->front;
                pToConga->front->previous = this->back;
                this->back = pToConga->back;
                pToConga->front = nullptr;
                mergeIsSuccessful = true;
            }
            break;
    }
}

void LinkedList::Node::printUniversity() const
{
    switch (this->university) {
        case FMI:
            std::cout << "FMI";
            break;
        case TU:
            std::cout << "TU";
            break;
        case UNSS:
            std::cout << "UNSS";
    }
}

void LinkedList::printList() const
{
    Node* temp = front;
    while(temp != back)
    {
        std::cout << '(' <<
        temp->name << ", ";
        temp->printUniversity();
        std::cout << ')' <<
        " - ";
        temp = temp->next;
    }
    std::cout << '(' <<
    back->name << ", ";
    back->printUniversity();
    std::cout << ')';
}

void LinkedList::append(const char* name, University university)
{
    switch (university) {
        case FMI:
            if(back->university == UNSS)
            {
                std::cout << "Incompatible people\n";
                return;
            }
            else
            {
                pushBack(name, university);
            }
            break;
        case TU:
            if(back->university == FMI)
            {
                std::cout << "Incompatible people\n";
                return;
            }
            else
            {
                pushBack(name, university);
            }
            break;
        case UNSS:
            if(back->university == TU)
            {
                std::cout << "Incompatible people\n";
                return;
            }
            else
            {
                pushBack(name, university);
            }
            break;
        default:
            std::cout << "Invalid university\n";
            return;
    }
}
