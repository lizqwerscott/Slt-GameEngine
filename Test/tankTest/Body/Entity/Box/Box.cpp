#include "Box.h"
#include "../../Item/Item.h"

Box::Box(std::string name, GameObject *parent, double volume, double quality,
         b2Vec2 nodePos, double hp)
    : Entity(name, parent, nodePos, hp), m_maxVolume(volume),
      m_maxQuality(quality), m_nowVolume(0), m_nowQuality(0) {}

Box::~Box() {}

bool Box::addItem(Item *item)
{
    bool qualityP = item->getQuality() <= this->m_maxQuality - this->m_nowQuality;
    bool volumeP = item->getVolume() <= this->m_maxVolume - this->m_nowVolume;
    bool addP = qualityP && volumeP;
    if (addP) {
        this->AddChild(item);
        this->m_nowQuality -= item->getQuality();
        this->m_nowVolume -= item->getVolume();
    }
    return addP;
}

Item *Box::getItem(std::string name)
{
    return static_cast<Item *>(this->GetChild(name));
}

Item *Box::transferItem(std::string name)
{
    Item *item = getItem(name);
    if (item != nullptr) {
        this->popChild(name);
        this->m_nowQuality += item->getQuality();
        this->m_maxVolume += item->getVolume();
    }
    return item;
}
