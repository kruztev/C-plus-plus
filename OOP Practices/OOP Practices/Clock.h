//
//  Clock.h
//  OOP Practices
//

#ifndef Clock_h
#define Clock_h

class Clock
{
public:
    Clock();
    Clock(const unsigned, const unsigned, const unsigned);
    Clock(const Clock&);
    Clock& operator=(const Clock&);
    Clock operator+(const Clock&);
    ~Clock();
    
public:
    void setHours(unsigned);
    void setMinutes(unsigned);
    void setSeconds(unsigned);

public:
    void setClock(unsigned, unsigned, unsigned);
    void print();
    void nextTick();
    void syncTime();
    
private:
    unsigned hours;
    unsigned minutes;
    unsigned seconds;
};

#endif
