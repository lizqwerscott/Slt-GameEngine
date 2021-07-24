#include "Cube.h"

Cube::Cube(std::string name, GameObject * parent, PhysicalWorld * world, b2Vec2 size, b2Vec2 nodePos, double hp) :
    Entity(name, parent, nodePos, hp)
{
    this->SetPosition(nodePos);
    b2Vec2 localWorldPos(0, 0);
    b2BodyDef bodyDef;
    bodyDef.type = b2BodyType::b2_dynamicBody;
    bodyDef.position =
        Math::WorldCoordSToPhysicalCoordS(nodePos + localWorldPos);
    bodyDef.angle = 0;
    bodyDef.bullet = true;
    auto physicalBody = CreatePhysicalBody(std::string("CubeBody"), localWorldPos, bodyDef, world);
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
    auto fixture = physicalBody->CreateFixture(std::string("CubeFixture"), fixtureDef);
    physicalBody->GetBody()->GetUserData().data.push_back(static_cast<void*>(this));
    fixture->m_fixture->GetUserData().data.push_back(static_cast<void*>(this));
    this->m_isDrawUi = false;
}
