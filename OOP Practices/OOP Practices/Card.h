//
//  Card.h
//  OOP Practices
//


#ifndef Card_h
#define Card_h

const unsigned short NAME_MAX_LENGTH = 25;
const unsigned short DEFENCE_POINTS_DEFAULT = 0;
const unsigned short ATTACK_POINTS_DEFAULT = 0;
const unsigned short DEFENCE_POINTS_MIN = 0;
const unsigned short DEFENCE_POINTS_MAX = 5000;
const unsigned short ATTACK_POINTS_MIN = 0;
const unsigned short ATTACK_POINTS_MAX = 5000;

class Card
{
public:
    Card();
   // Card(char name[NAME_MAX_LENGTH]);
    
    void setName(const char[]);
    void setType(bool);
    void setDefencePoints(unsigned int);
    void setAttackPoints(unsigned int);
    
    bool getType() const;
    const char* getName() const;
    unsigned int getDefencePoints() const;
    unsigned int getAttackPoints() const;
    
private:
    bool isMonster;
    char name[NAME_MAX_LENGTH];
    unsigned int defencePoints;
    unsigned int attackPoints;
};

#endif
