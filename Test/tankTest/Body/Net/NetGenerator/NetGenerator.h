#ifndef NETGENERATOR_H
#define NETGENERATOR_H

#include "../NetEnergy/NetEnergy.h"

class NetGenerator : public NetEnergy
{
public:
    NetGenerator(float generatorSpeed, float energyMax);
    virtual ~NetGenerator();
public:
    virtual void UpdateSelf(sf::Time &dt) override;
public:
    float getSpeed();
    float getMax();
    float getSaveEnergy();
private:
    float m_generatorSpeed;
    float m_generatorEnergyMax;
    float m_generatorEnergy;
};


#endif
