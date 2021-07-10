#ifndef ITEM_H
#define ITEM_H

#include "../GameObject.h"

using namespace slt;

class Item : public GameObject
{
public:
    Item(std::string name, GameObject * parent, double volume, double quality, double hp = 1);
    ~Item();
public:
    double getVolume() {return m_volume;}
    double getQuality() {return m_quality;}
private:
    double m_volume;
    double m_quality;
};

#endif /* ITEM_H */
