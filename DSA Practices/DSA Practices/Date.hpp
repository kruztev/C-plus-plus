//
//  Date.hpp
//  SDP Practs
//

#ifndef Date_hpp
#define Date_hpp

const unsigned short DATE_SIZE = 11;

class Date
{
public:
    Date(const unsigned, const unsigned, const unsigned);
   const char* getDate() const;
private:
    char date[DATE_SIZE];
    
private:
    bool dateIsValid(const unsigned, const unsigned, const unsigned) const;
};

#endif
