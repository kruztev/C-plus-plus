//
//  User.h
//  DrinkBook
//

#ifndef User_h
#define User_h
#include "String.h"

enum MusicType
{
    FOLK = 0,
    HOUSE,
    ROCK,
    ALL
};

class User
{
public:
    User(const String& nName, unsigned nAge, unsigned nCash, unsigned nVodkas, unsigned nWhiskeys, const char* music);
    User(const User&) = default;
    User& operator=(const User&) = default;
    ~User() = default;
    
public:
    const String& getName() const;
    const unsigned getAge() const;
    const unsigned getCash() const;
    const unsigned getVodkas() const;
    const unsigned getWhiskeys() const;
    const MusicType getMusicType() const;
    
    void setName(const String&);
    void setAge(unsigned);
    void setCash(unsigned);
    void setVodkas(unsigned);
    void setWhiskeys(unsigned);
    void setMusic(const char*);
    
private:
    String name;
    unsigned age;
    unsigned cash;
    unsigned vodkas;
    unsigned whiskeys;
    MusicType music;
};



#endif
