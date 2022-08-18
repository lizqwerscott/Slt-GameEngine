#include "NetControlDevice.h"
#include "../NetWire/NetWire.h"

NetControlDevice::NetControlDevice() : NetControl("device")
{

}

NetControlDevice::~NetControlDevice()
{
    this->subscribeRecives.clear();
}

void NetControlDevice::UpdateSelf(sf::Time &dt)
{

}

void NetControlDevice::sendSignal(DeviceSignalData & data)
{
    for (auto net : this->m_connectNets) {
	if (net->m_typename == "NetControl") {
	    auto controlNet = static_cast<NetControl *>(net);
	    if (controlNet->m_controlTypeName == "wire") {
		auto wire = static_cast<NetWire *>(controlNet);
		wire->passSignal(this, data);
	    }

	    if (controlNet->m_controlTypeName == "device") {
		auto device = static_cast<NetControlDevice *>(controlNet);
		device->reciveSignal(data);
	    }
	}
    }
}

void NetControlDevice::reciveSignal(DeviceSignalData & data)
{
    auto funs = this->subscribeRecives[data.type];
    for (auto fun : funs) {
	fun(data);
    }
}

void NetControlDevice::subscribeRecive(DeviceSignalType type, SignalReciveFunction fun)
{
    this->subscribeRecives[type].push_back(fun);
}
