#include "NetUse.h"

NetUse::NetUse(float energyMax, float energyUseSpeed) :
    NetEnergy("NetUse"),
    m_energyUseSpeed(energyUseSpeed),
    m_energyMax(energyMax),
    m_energy(0)
{
    
}

NetUse::~NetUse()
{
    
}

void NetUse::UpdateSelf(sf::Time &dt)
{
    // use energy
    if (this->m_energy >= 0) {
	float step = dt.asSeconds() / 1 * this->m_energyUseSpeed;
	m_energy -= step;
    }
    // get energy
    if (this->m_energy <= this->m_energyMax) {
    }
}

