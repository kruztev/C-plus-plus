//
//  Card.cpp
//  OOP Practices
//

#include <iostream>
#include "Card.h"

Card::Card() : isMonster(true), name("Token"), defencePoints(DEFENCE_POINTS_DEFAULT), attackPoints(ATTACK_POINTS_DEFAULT)
{}

void Card::setName(const char name[])
{
    if (strlen(name) > NAME_MAX_LENGTH)
    {
        std::cerr << "Max name length is " << NAME_MAX_LENGTH << '\n';
        strcpy(this->name,"\0");
        return;
    }
    strcpy(this->name, name);
}

void Card::setType(bool value)
{
    isMonster = value;
}

void Card::setDefencePoints(unsigned int points)
{
    if (points > DEFENCE_POINTS_MAX)
    {
        defencePoints = DEFENCE_POINTS_MAX;
        return;
    }
    defencePoints = DEFENCE_POINTS_MAX;
}

void Card::setAttackPoints(unsigned int points)
{
    if (points > ATTACK_POINTS_MAX)
    {
        attackPoints = ATTACK_POINTS_MAX;
        return;
    }
    attackPoints = points;
}

unsigned int Card::getAttackPoints() const
{
    return attackPoints;
}

bool Card::getType() const
{
    return isMonster;
}

unsigned int Card::getDefencePoints() const
{
    return defencePoints;
}

const char* Card::getName() const
{
    return name;
}
