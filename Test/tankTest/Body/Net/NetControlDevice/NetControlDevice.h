#ifndef NETCONTROLDEVICE_H
#define NETCONTROLDEVICE_H

#include "../NetControl/NetControl.h"

class NetControlDevice : public NetControl
{
public:
    NetControlDevice();
    virtual ~NetControlDevice();
public:
    virtual void UpdateSelf(sf::Time &dt) override;
};

#endif
