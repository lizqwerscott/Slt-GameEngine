#ifndef BOX_H
#define BOX_H

#include "../Entity.h"
#include "../../BoxBase.h"

using namespace slt;

class Item;

class Box : public Entity, BoxBase
{
public:
    Box(std::string name, GameObject * parent, double volume, double quality, b2Vec2 nodePos = b2Vec2(0, 0), double hp = 1);
    ~Box();
};

#endif /* BOX_H */
