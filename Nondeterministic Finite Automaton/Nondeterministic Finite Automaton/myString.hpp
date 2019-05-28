//
//  myString.hpp
//  Nondeterministic Finite Automaton
//


#ifndef myString_hpp
#define myString_hpp
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
    const unsigned getLen() const;
    
private:
    void copy(const String&);
    void free();
    
private:
    char* str;
    unsigned len;
};

String::String()
{
    try {
        str = new char[STARTING_LEN];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Bad alloc caught: " << ba.what() << '\n';
        throw;
    }
    *str = '\0';
    len = 1;
}

String::String(const char* rhs)
{
    try {
        str = new char[strlen(rhs) + 1];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Bad alloc caught: " << ba.what() << '\n';
        throw;
    }
    strcpy(str, rhs);
    len = strlen(rhs);
}

String::String(const String& rhs)
{
    copy(rhs);
}

String& String::operator=(const String& rhs)
{
    if (&rhs != this)
    {
        free();
        copy(rhs);
    }
    return *this;
}

String::~String()
{
    free();
}

const char String::operator[](size_t index) const
{
    try {
        if (index < 0 || index > len - 1)
            throw std::invalid_argument("Invalid index");
    } catch (const std::invalid_argument& excp) {
        std::cerr << "Exception caught: " << excp.what() << '\n';
        throw;
    }
    return str[index];
}

char String::operator[](size_t index)
{
    try {
        if (index < 0 || index > len - 1)
            throw std::invalid_argument("Invalid index");
    } catch (const std::invalid_argument& excp) {
        std::cerr << "Exception caught: " << excp.what() << '\n';
        throw;
    }
    return str[index];
}

void String::copy(const String& rhs)
{
    try {
        str = new char[rhs.len + 1];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Bad alloc caught: " << ba.what() << '\n';
        throw;
    }
    strcpy(str, rhs.str);
    len = rhs.len;
}

void String::free()
{
    delete[] str;
}

#endif
