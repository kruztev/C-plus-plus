//
//  FilmStar.hpp
//


#ifndef FilmStar_h
#define FilmStar_h

const unsigned int MAX_NAME_LENGTH = 256;

class FilmStar
{
public:
    void setId(const unsigned long long);
    void setFirstName(const char[]);
    void setLastName(const char[]);
    void setFilms(const unsigned long long);
    
    unsigned long long getId() const;
    const char* getFirstName() const;
    const char* getLastName() const;
    unsigned long long getFilms() const;
    
private:
    unsigned long long Id;
    char FirstName[MAX_NAME_LENGTH];
    char LastName[MAX_NAME_LENGTH];
    unsigned long long Films;
};

#endif
