#include "Cube.h"

Cube::Cube(std::string name, GameObject * parent, PhysicalWorld * world, b2Vec2 size, b2Vec2 nodePos, double hp) :
    Entity(name, parent, nodePos, hp)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2BodyType::b2_dynamicBody;
    bodyDef.position =
        Math::WorldCoordSToPhysicalCoordS(nodePos);
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

    ////auto sprite = CreateSprite(std::string("cubeSprite")).get();
    //sf::RectangleShape * rectShape = new sf::RectangleShape();
    //rectShape->setSize(Math::SLTToPixel(b2Vec2(size.x * 2, size.y * 2)));
    //rectShape->setOrigin(Math::SLTToPixel(b2Vec2(size.x, size.y)));
    //rectShape->setTexture(tieTexture);
    //rectShape->setTextureRect(sf::IntRect(0, 0, 100, 100));
    //InsertShape(std::string("tieShape"), rectShape);
}
