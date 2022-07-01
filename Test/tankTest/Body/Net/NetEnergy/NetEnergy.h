#ifndef NETENERGY_H
#define NETENERGY_H

#include "../Net.h"

class NetEnergy : public Net
{
public:
    NetEnergy(std::string typeName);
    virtual ~NetEnergy();
public:
    virtual void UpdateSelf(sf::Time &dt) override;
public:
    float getEnergy(NetEnergy * root = nullptr);
    float runNode(std::vector<NetEnergy *> searchs);
public:
    std::string m_energyTypeName;
};

#endif
