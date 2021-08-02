#include "Bullet.h"

Bullet::Bullet(std::string name, GameObject * parent, PhysicalWorld * world, b2Vec2 nodePos, b2Vec2 initSpeed) :
    Entity(name, parent, nodePos, 1)
{
    b2Vec2 localWorldPos(0, 0);
    b2BodyDef bodyDef;
    bodyDef.type = b2BodyType::b2_dynamicBody;
    bodyDef.position =
        Math::WorldCoordSToPhysicalCoordS(this->GetPosition() + localWorldPos);
    bodyDef.angle = 0;
    bodyDef.bullet = true;

    auto physicalBody = this->CreatePhysicalBody(
                            std::string("BulletBody"), localWorldPos, bodyDef,
                            world);

    b2CircleShape circleShape;
    circleShape.m_p = b2Vec2(0, 0);
    circleShape.m_radius = 0.2; // radius
    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.1;
    fixtureDef.friction = 0.3;
    fixtureDef.shape = &circleShape;
    fixtureDef.restitution = 1;
    auto fixture = physicalBody->CreateFixture(std::string("fixture"),
                   fixtureDef);
    physicalBody->GetBody()->ApplyLinearImpulseToCenter(initSpeed, true);
    this->GetPhysicalBody()->GetBody()->GetUserData().data.push_back(static_cast<void *>(this));
    fixture->m_fixture->GetUserData().data.push_back(static_cast<void*>(this));

    sf::Texture * bulletTexture = ResourceManager::GetTexture(std::string("bullet1"));
    bulletTexture->setSmooth(true);

    CreateRectangleShape(std::string("bullet"), b2Vec2(0.2, 0.2), bulletTexture);
}

