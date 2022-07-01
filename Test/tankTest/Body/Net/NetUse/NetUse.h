#ifndef NETUSE_H
#define NETUSE_H

#include "../NetEnergy/NetEnergy.h"

class NetUse : public NetEnergy
{
public:
    NetUse(float energyMax, float energyUseSpeed = 1);
    virtual ~NetUse();
public:
    virtual void UpdateSelf(sf::Time &dt) override;
private:
    float m_energyUseSpeed;
    float m_energyMax;
    float m_energy;
};

#endif
