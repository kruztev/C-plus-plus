//
//  myString.cpp
//  Nondeterministic Finite Automaton
//


#include "String.h"

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

const unsigned String::getLen() const
{
    return len;
}

bool String::operator==(const String& rhs) const
{
    if (len != rhs.len)
        return false;
    for (size_t i = 0; i < len; ++i)
    {
        if (str[i] != rhs.str[i])
            return false;
    }
    return true;
}
