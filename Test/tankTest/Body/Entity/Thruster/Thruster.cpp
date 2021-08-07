#include "Thruster.h"

Thruster::Thruster(std::string name, GameObject * parent, b2Vec2 size, float maxThrust, b2Vec2 nodePos, double hp) :
    Entity(name, parent, nodePos, hp),
    m_thrust(0),
    m_maxThrust(maxThrust)
{
    this->m_isDrawUi = false;

    sf::Texture * tieTexture = ResourceManager::GetTexture(std::string("tie"));
    tieTexture->setSmooth(true);

    m_mainShape = CreateRectangleShape(size, tieTexture);
}

void Thruster::increaseThrust(float step)
{
    if (m_thrust + step <= m_maxThrust) {
        m_thrust += step;
    }
}

void Thruster::decreaseThrust(float step)
{
    if (m_thrust - step >= 0) {
        m_thrust -= step;
    }
}

void Thruster::push()
{
    b2Vec2 back(0, -1);
    m_physicalBody->GetBody()->ApplyForceToCenter(b2Vec2(back.x * m_thrust, back.y * m_thrust), true);
}

