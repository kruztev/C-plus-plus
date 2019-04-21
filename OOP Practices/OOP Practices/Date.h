//
//  Date.h
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
    
    void setDay(unsigned int);
    void setMonth(unsigned int);
    void setYear(unsigned int);
    
    unsigned int getDay() const;
    unsigned int getMonth() const;
    unsigned int getYear() const;
    
    
private: // Helper functions
    bool isValidDate(unsigned int, unsigned int, unsigned int) const;
    void handleDayAddition(unsigned int, unsigned short);
    void handleDaySubtraction(unsigned int, unsigned short);
    
private:
    unsigned int day;
    unsigned int month;
    unsigned int year;
};

Date getDifference(const Date&, const Date&);

#endif
