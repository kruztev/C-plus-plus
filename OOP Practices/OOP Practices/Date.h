//
//  Date.hpp
//  OOP Practices
//


#ifndef Date_h
#define Date_h

class Date
{
public:
    Date();
    Date(unsigned int, unsigned int, unsigned int);
    
public:
    void addDays(unsigned int);
    void subtractDays(unsigned int);
    bool isLeap() const;
    unsigned int daysToChristmas() const;
    bool isLaterThan(const Date&) const;
    
private: // Helper functions
    bool isValidDate(unsigned int, unsigned int, unsigned int) const;
    unsigned int calculateMonths(unsigned int, unsigned int) const;
    
private:
    unsigned int day;
    unsigned int month;
    unsigned int year;
};

Date& getDifference(const Date&, const Date&);

#endif