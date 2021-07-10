#include "Person.h"

Person::Person(std::string name, GameObject * parent, b2Vec2 nodePos) :
    Biological(name, parent, nodePos, 100),
    m_water(100),
    m_food(100)
{
}

Person::~Person() {}

void Person::useLeftHand()
{
}

void Person::useRightHand()
{
}

void Person::move()
{
}

void Person::drink(GameObject * drink)
{
}

void Person::eat(GameObject * food)
{
}

void Person::wear(GameObject * clothes)
{
}

