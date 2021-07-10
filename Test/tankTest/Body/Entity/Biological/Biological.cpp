#include "Biological.h"

Biological::Biological(std::string name, GameObject * parent, b2Vec2 nodePos, double hp) : 
    Entity(name, parent, nodePos, hp)
{
}

Biological::~Biological()
{
}

