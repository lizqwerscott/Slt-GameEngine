#include "Thruster.h"

Thruster::Thruster(std::string name, GameObject * parent, PhysicalWorld * world, b2Vec2 size, float maxThrust, b2Vec2 nodePos, double hp) :
    Entity(name, parent, nodePos, hp),
    m_thrust(0),
    m_maxThrust(maxThrust)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2BodyType::b2_dynamicBody;
    bodyDef.position = Math::WorldCoordSToPhysicalCoordS(nodePos);
    bodyDef.angle = 0;
    bodyDef.bullet = true;
    b2PolygonShape polygonShape;

    if (size.x > 1 && size.y > 1) {
        polygonShape.SetAsBox(size.x, size.y, b2Vec2(0, 0), 0);
    } else {
        polygonShape.SetAsBox(1, 1, b2Vec2(0, 0), 0);
    }
    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.5;
    fixtureDef.friction = 0.2;
    fixtureDef.restitution = 1;
    fixtureDef.shape = &polygonShape;
    initPhysical(bodyDef, fixtureDef, world, "CubeBody", "CubeFixture");

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

