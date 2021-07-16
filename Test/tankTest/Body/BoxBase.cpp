#include "BoxBase.h"
#include "Item/Item.h"

BoxBase::BoxBase(double volume, double quality) :
    m_maxVolume(volume),
    m_maxQuality(quality)
{
}

BoxBase::~BoxBase()
{
    for (auto items : m_container) {
        for (auto item : items.second) {
            delete item;
            item = nullptr;
        }
        items.second.clear();
    }
    m_container.clear();
}

bool BoxBase::addItem(Item * item)
{
    bool qualityP = item->getQuality() <= this->m_maxQuality - this->m_nowQuality;
    bool volumeP = item->getVolume() <= this->m_maxVolume - this->m_nowVolume;
    bool addP = qualityP && volumeP;
    if (addP) {
        //this->m_container.push_back(item);
        this->m_container[item->getName()].push_back(item);
        this->m_nowQuality -= item->getQuality();
        this->m_nowVolume -= item->getVolume();
    }
    return addP;
}

std::vector<Item *>
BoxBase::getItem(std::string name, int number)
{
    std::vector<Item *> m_result;
    auto iter = m_container.find(name);
    if (iter != m_container.end()) {
        if (static_cast<int>(iter->second.size()) >= number) {
            for (int i = 0; i < number; i++) {
                m_result.push_back(iter->second[i]);
                iter->second.erase(iter->second.begin() + i);
            }
        }
    }
    return m_result;
}

bool BoxBase::transferItem(std::string name, BoxBase * target, int number)
{
    auto iter = m_container.find(name);
    if (iter != m_container.end()) {
        if (static_cast<int>(iter->second.size()) >= number) {
            for (int i = 0; i < number; i++) {
                target->addItem(iter->second[i]);
                iter->second.erase(iter->second.begin() + i);
            }
            return true;
        } else {
            printf("number bigger than have\n");
            return false;
        }
    }
    return false;
    // auto iter = find_if(m_container.begin(), m_container.end(), [name](Item * item) {
    //     return name == item->getName();
    // });
    // bool addP = false;
    // if (iter != this->m_container.end()) {
    //     Item * item = *iter;
    //     m_container.erase(iter);
    //     this->m_nowQuality += item->getQuality();
    //     this->m_maxVolume += item->getVolume();
    //     addP = target->addItem(item);
    // }
    // return addP;
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
