#ifndef BOX_H
#define BOX_H

#include "../Entity.h"

using namespace slt;

class Item;

class Box : public Entity
{
public:
    Box(std::string name, GameObject * parent, double volume, double quality, b2Vec2 nodePos = b2Vec2(0, 0), double hp = 1);
    ~Box();
public:
    bool addItem(Item * item);
    Item * getItem(std::string name);
    Item * transferItem(std::string name);
public:
    double getNowVolume() {return m_nowVolume;}
    double getNowQuality() {return m_nowQuality;}
    double getMaxVolume() {return m_maxVolume;}
    double getMaxQuality() {return m_maxQuality;}
    void setMaxVolume(double volume) { m_maxVolume = volume;}
    void setMaxQuality(double quality) { m_maxQuality = quality;}
private:
    double m_maxVolume;
    double m_maxQuality;
    double m_nowVolume;
    double m_nowQuality;
};

#endif /* BOX_H */
