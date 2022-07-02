#include "NetWire.h"

NetWire::NetWire() : NetEnergy("NetWire", 0)
{
    
}

NetWire::~NetWire()
{
    
}


float NetWire::getEnergy(float needEnergy)
{
    std::vector<NetEnergy *> searchs;
    return this->runNode(searchs, needEnergy);
}

