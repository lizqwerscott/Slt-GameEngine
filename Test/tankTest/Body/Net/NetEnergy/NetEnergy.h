#ifndef NETENERGY_H
#define NETENERGY_H

#include "../Net.h"

class NetEnergy : public Net
{
public:
    NetEnergy();
    virtual ~NetEnergy();
public:
    float getEnergy(NetEnergy * root = nullptr);
    float runNode(std::vector<NetEnergy *> searchs);
};

#endif
