#include "BoxBase.h"
#include "Item/Item.h"

BoxBase::BoxBase(double volume, double quality) :
    m_maxVolume(volume),
    m_maxQuality(quality)
{
}

BoxBase::~BoxBase()
{
}

bool BoxBase::addItem(Item * item)
{
    bool qualityP = item->getQuality() <= this->m_maxQuality - this->m_nowQuality;
    bool volumeP = item->getVolume() <= this->m_maxVolume - this->m_nowVolume;
    bool addP = qualityP && volumeP;
    if (addP) {
        this->m_container.push_back(item);
        this->m_nowQuality -= item->getQuality();
        this->m_nowVolume -= item->getVolume();
    }
    return addP;
}

Item * BoxBase::getItem(std::string name)
{
    auto iter = find_if(m_container.begin(), m_container.end(), [name](Item * item) {
        return name == item->getName();
    });

    if (iter != this->m_container.end()) {
        return *iter;
    } else {
        return nullptr;
    }
}

Item * BoxBase::getItem(int index)
{
    return m_container[index];
}

bool BoxBase::transferItem(std::string name, BoxBase * target)
{
    auto iter = find_if(m_container.begin(), m_container.end(), [name](Item * item) {
        return name == item->getName();
    });
    bool addP = false;
    if (iter != this->m_container.end()) {
        Item * item = *iter;
        m_container.erase(iter);
        this->m_nowQuality += item->getQuality();
        this->m_maxVolume += item->getVolume();
        addP = target->addItem(item);
    }
    return addP;
}

double BoxBase::getNowVolume()
{
    return m_nowVolume;
}

double BoxBase::getNowQuality()
{
    return m_nowQuality;
}

double BoxBase::getMaxVolume()
{
    return m_maxVolume;
}

double BoxBase::getMaxQuality()
{
    return m_maxQuality;
}

void BoxBase::setMaxVolume(double volume)
{
    m_maxVolume = volume;
}

void BoxBase::setMaxQuality(double quality)
{
    m_maxQuality = quality;
}
