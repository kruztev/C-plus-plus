//  Code ran and tested on Clang (Xcode Version 10.1)
//
//  LinkedList.hpp
//  Conga
//

#ifndef LinkedList_hpp
#define LinkedList_hpp

enum University
{
    INVALID_UNIVERSITY = -1,
    FMI,
    TU,
    UNSS,
    UNIVERSITIES_COUNT
};

class LinkedList
{
private:
    class Node
    {
    public:
        Node();
        Node(const char*, University);
        ~Node();
        
    public:
        void printUniversity() const;
        
    public:
        char* name;
        University university;
        Node* next;
        Node* previous;
    };
    
public:
    LinkedList();
    LinkedList(const char*, University);
    LinkedList(const LinkedList&);
    LinkedList(Node*);
    LinkedList& operator=(const LinkedList&);
    ~LinkedList();
    
public:
    void pushBack(const char*, University);
    void popBack();
    void popFront();
    unsigned getSize() const;
    LinkedList* removeByNameNode(const char*, short&);
    void mergeLists(LinkedList*, bool&);
    void printList() const;
    void append(const char*, University);

    
private:
    void clear();
    void copy(const LinkedList&);
    void setSize();

private:
    Node* front;
    Node* back;
    unsigned size;
    
};

#endif
