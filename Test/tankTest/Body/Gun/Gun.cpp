#include "Gun.h"
#include "../Bullet/Bullet.h"

Gun::Gun(std::string name, GameObject * parent, PhysicalWorld * world, b2Vec2 nodePos) :
    GameObject(name, parent, nodePos, 10000),
    m_bulletN(0)
{
    b2Vec2 localWorldPos(0, 0);
    b2BodyDef bodyDef;
    bodyDef.type = b2BodyType::b2_dynamicBody;
    bodyDef.position =
        Math::WorldCoordSToPhysicalCoordS(nodePos + localWorldPos);
    bodyDef.angle = 0;
    bodyDef.bullet = true;

    auto physicalBody = this->CreatePhysicalBody(std::string("GunBody"), localWorldPos, bodyDef, world);

    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(3, 10, b2Vec2(0, 0), 0);
    b2FixtureDef fixtureDef;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.5;
    fixtureDef.restitution = 1;
    fixtureDef.shape = &polygonShape;
    auto fixture = physicalBody->CreateFixture(std::string("fixture"), fixtureDef);
    this->GetPhysicalBody()->GetBody()->GetUserData().data.push_back(static_cast<void *>(this));
}

void Gun::fire(SNode * parent, PhysicalWorld * world)
{
    std::string bulletName = std::string("bullet") + std::to_string(m_bulletN);
    b2Vec2 bulletPos = GetPosition() + b2Vec2(0, 10.5);
    new Bullet(bulletName, static_cast<GameObject *>(parent), world, bulletPos, b2Vec2(0, 30));
    printf("[CreateBullet]:%s, pos:%f,%f\n", bulletName.c_str(), bulletPos.x, bulletPos.y);
    m_bulletN++;
}
