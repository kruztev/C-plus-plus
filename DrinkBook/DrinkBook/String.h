//
//  String.h
//  Nondeterministic Finite Automaton
//


#ifndef String_h
#define String_h
#include <iostream>

const unsigned short STARTING_LEN = 1;

class String
{
public:
    String();
    String(const char*);
    String(const String&);
    String& operator=(const String&);
    ~String();
    const char operator[](size_t) const;
    char operator[](size_t);
    bool operator==(const String&) const;
    const unsigned getLen() const;
    
private:
    void copy(const String&);
    void free();
    
private:
    char* str;
    unsigned len;
};

#endif
