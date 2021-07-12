#ifndef PERSON_H
#define PERSON_H

#include "Biological.h"

class Item;
//class Clothes;
//class Hat;
//class Gloves;
//class Coat;
//class Pants;
//class Shoes;
class Bag;

class Person : public Biological
{
public:
    Person(std::string name, GameObject * parent, PhysicalWorld * world, b2Vec2 nodePos = b2Vec2(0, 0));
    ~Person();
public:
    void useHand(PhysicalWorld * world, b2Vec2 mouseClick);
    bool handP() {return m_tHand != nullptr;}
    Item * getHand();
public:
    void move();
    void drink(Item * drink);
    void eat(Item * food);
    void wear(Item * clothes);
    bool equip(Item * tool);
private:
    //self item tools
    //hand
    Item * m_tHand = nullptr;
    //Backpack
    Bag * m_tBackPack = nullptr;
    //clothes
    //Hat * m_cHead = nullptr;

    //Gloves * m_cLeftHand = nullptr; //only put clothes
    //Gloves * m_cRightHand = nullptr; //only pub clothes

    // Coat * m_cBody = nullptr;
    //
    // Pants * m_cLeg;
    //
    // Shoes * m_cLeftFoot = nullptr;
    // Shoes * m_cRightFoot = nullptr;

    //Attributes 
    double m_water;
    double m_food;
};

#endif /* PERSON_H */
