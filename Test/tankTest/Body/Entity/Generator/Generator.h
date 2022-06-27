#ifndef GENERATOR_H
#define GENERATOR_H

#include "../Entity.h"

class Generator : public Entity
{
public:
    Generator(std::string name, GameObject * parent, b2Vec2 nodePos, b2Vec2 size, double hp = 100);
    virtual ~Generator() {}
public:
    virtual void onFace(Person * person) {}
};

#endif
