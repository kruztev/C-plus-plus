//
//  Plane.cpp
//  OOP Practices
//


#include "Plane.h"

int Plane::calcFlightTime(double startPosition, double endPosition)
{
    int time = (endPosition - startPosition) / speed;
    return time;
}

std::string Plane::getType() const
{
    return type;
}

double Plane::getSpeed() const
{
    return speed;
}

int Plane::getAttackPoints() const
{
    return attackPoints;
}

void Plane::setType(const std::string& type)
{
    this->type = type;
}

void Plane::setSpeed(int speed)
{
    this->speed = speed;
}

void Plane::setAttackPoints(int attackPoints)
{
    this->attackPoints = attackPoints;
}
