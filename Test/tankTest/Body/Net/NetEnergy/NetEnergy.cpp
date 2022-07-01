#include "NetEnergy.h"
#include <algorithm>

NetEnergy::NetEnergy(std::string typeName) :
    Net("Energy"),
    m_energyTypeName(typeName)
{
    
}

NetEnergy::~NetEnergy()
{
    
}

void NetEnergy::UpdateSelf(sf::Time &dt)
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
