#include "Item.h"


Item::Item(std::string name, GameObject * parent, double volume, double quality, double hp) : 
    GameObject(name, parent, hp),
    m_volume(volume),
    m_quality(quality)
{
}

Item::~Item() {}

