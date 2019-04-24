//
//  Plane.h
//  OOP Practices
//

#ifndef Plane_hpp
#define Plane_hpp

#include <string>

class Plane
{
public:
    virtual std::string getType() const;
    virtual double getSpeed() const;
    virtual int getAttackPoints() const;
    virtual int calcFlightTime(double, double);
    virtual void setType(const std::string&);
    virtual void setSpeed(int);
    virtual void setAttackPoints(int);
    virtual void fly() = 0;
    virtual void attack(const Plane*) = 0;
    
private:
    std::string type;
    double speed;
    int attackPoints;
};


#endif
