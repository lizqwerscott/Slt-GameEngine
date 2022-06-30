#include "NetEnergy.h"
#include <algorithm>

NetEnergy::NetEnergy() : Net("Energy")
{
    
}

NetEnergy::~NetEnergy()
{
    
}

float NetEnergy::getEnergy(NetEnergy * root)
{
    for (auto net : this->m_connectNets) {
	if (net->m_typename == "Energy") {
	    auto energy = static_cast<NetEnergy *>(net);
	    energy->getEnergy(this);
	}
    }
}

float NetEnergy::runNode(std::vector<NetEnergy *> searchs)
{
    for (auto net : this->m_connectNets) {
	if (net->m_typename == "Energy") {
	    auto energy = static_cast<NetEnergy *>(net);
	    auto it = find(searchs.begin(), searchs.end(), energy);
	    if (it != searchs.end()) {

	    } else {
		energy->getEnergy(this);
	    }
	}
    }
}
