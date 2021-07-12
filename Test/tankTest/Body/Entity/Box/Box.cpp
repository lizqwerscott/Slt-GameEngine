#include "Box.h"
#include "../../Item/Item.h"

Box::Box(std::string name, GameObject *parent, double volume, double quality,
         b2Vec2 nodePos, double hp) :
    Entity(name, parent, nodePos, hp),
    BoxBase(volume, quality)
{
}

Box::~Box() {}

