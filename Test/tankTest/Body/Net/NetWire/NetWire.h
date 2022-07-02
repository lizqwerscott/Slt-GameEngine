#ifndef NETWIRE_H
#define NETWIRE_H

#include "../NetEnergy/NetEnergy.h"

class NetWire : public NetEnergy
{
public:
    NetWire();
    virtual ~NetWire();
public:
    virtual float getEnergy(float needEnergy) override;
};

#endif
