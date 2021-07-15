#ifndef ITEM_H
#define ITEM_H

#include "../../../../src/AllSub.h"

using namespace slt;

class Item
{
public:
    Item(std::string name, double volume, double quality) :
        m_volume(volume),
        m_quality(quality),
        m_name(name)
    {}
    ~Item() {}
public:
    double getVolume() {return m_volume;}
    double getQuality() {return m_quality;}
    std::string getName() {return m_name;}
private:
    double m_volume;
    double m_quality;
    std::string m_name;
    std::string m_typeName;
};

#endif /* ITEM_H */
