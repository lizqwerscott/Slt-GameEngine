#include "Item.h"

Item::Item(std::string name, double volume, double quality) : 
    m_volume(volume),
    m_quality(quality),
    m_name(name)
{
}

Item::~Item() {}

