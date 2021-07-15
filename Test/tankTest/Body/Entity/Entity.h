#ifndef ENTITY_H
#define ENTITY_H

#include "../GameObject.h"

using namespace slt;

class Person;

class Entity : public GameObject
{
public:
    Entity(std::string name, GameObject * parent, b2Vec2 nodePos = b2Vec2(0, 0), double hp = 1);
    ~Entity();
public:
    virtual void onFace(Person * person) {}
};

#endif /* ENTITY_H */
