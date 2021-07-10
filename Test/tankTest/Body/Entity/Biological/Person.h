#ifndef PERSON_H
#define PERSON_H

#include "Biological.h"

class Person : public Biological
{
public:
    Person(std::string name, GameObject * parent, b2Vec2 nodePos = b2Vec2(0, 0));
    ~Person();
public:
    void useLeftHand();
    void useRightHand();
public:
    void move();
    void drink(GameObject * drink);
    void eat(GameObject * food);
    void wear(GameObject * clothes);
private:
    //self item tools
    //left hand
    GameObject * m_tLeftHand = nullptr;
    //right hand
    GameObject * m_tRightHand = nullptr;
    //clothes
    GameObject * m_cHead = nullptr;

    GameObject * m_cLeftArm = nullptr;
    GameObject * m_cLeftHand = nullptr; //only put clothes

    GameObject * m_cRightArm = nullptr;
    GameObject * m_cRightHand = nullptr; //only pub clothes

    GameObject * m_cBody = nullptr;

    GameObject * m_cLeftLeg = nullptr;
    GameObject * m_cRightLeg = nullptr;

    GameObject * m_cLeftFoot = nullptr;
    GameObject * m_cRightFoot = nullptr;
    //Attributes 
    double m_water;
    double m_food;
};

#endif /* PERSON_H */
