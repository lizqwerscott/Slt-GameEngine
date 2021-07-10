#include "Entity.h"

Entity::Entity(std::string name, GameObject * parent, b2Vec2 nodePos, double hp) : 
    GameObject(name, parent, hp)
{
    this->SetPosition(nodePos);
}

Entity::~Entity() {}
