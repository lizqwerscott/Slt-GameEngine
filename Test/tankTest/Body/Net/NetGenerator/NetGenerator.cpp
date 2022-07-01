#include "NetGenerator.h"

NetGenerator::NetGenerator(float generatorSpeed, float energyMax) :
    NetEnergy("NetGneerator"),
    m_generatorSpeed(generatorSpeed),
    m_generatorEnergyMax(energyMax),
    m_generatorEnergy(0)
{
    
}

NetGenerator::~NetGenerator()
{
    
}

void NetGenerator::UpdateSelf(sf::Time &dt)
{
    if (m_generatorEnergy <= m_generatorEnergyMax) {
	Log::setLevel(LOG_LEVEL_INFO);
	double step = dt.asSeconds() / 1 * m_generatorSpeed;
	m_generatorEnergy += step;
	// Log::printLog("dt: %lf\n", dt.asSeconds());
	// Log::printLog("step: %lf, energy: %f\n", step, m_generatorEnergy);
    }
}

float NetGenerator::getSpeed()
{
    return this->m_generatorSpeed;
}

float NetGenerator::getMax()
{
    return this->m_generatorEnergyMax;
}

float NetGenerator::getSaveEnergy()
{
    return this->m_generatorEnergy;
}
