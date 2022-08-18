#ifndef NETCONTROLDEVICE_H
#define NETCONTROLDEVICE_H

#include "../NetControl/NetControl.h"
#include <map>

class NetControlDevice : public NetControl
{
public:
    NetControlDevice();
    virtual ~NetControlDevice();
public:
    virtual void UpdateSelf(sf::Time &dt) override;
public:
    void sendSignal(DeviceSignalData &data);
    void reciveSignal(DeviceSignalData &data);
public:
    void subscribeRecive(DeviceSignalType type, SignalReciveFunction fun);
private:
    std::map<DeviceSignalType, std::vector<SignalReciveFunction>> subscribeRecives;
};

#endif
