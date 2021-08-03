#include "Box.h"
#include "../../Item/Item.h"

Box::Box(std::string name, GameObject *parent, PhysicalWorld * world, double volume, double quality,
         b2Vec2 nodePos, double hp) :
    Entity(name, parent, nodePos, hp),
    BoxBase(volume, quality)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2BodyType::b2_dynamicBody;
    bodyDef.position = Math::WorldCoordSToPhysicalCoordS(nodePos);
    bodyDef.angle = 0;
    bodyDef.bullet = false;
    b2PolygonShape polygonShape;
    // polygonShape.SetAsBox(3, 1, Math::WorldCoordSToPhysicalCoordS(nodePos
    // + localWorldPos), 0);
    polygonShape.SetAsBox(2, 2, b2Vec2(0, 0), 0);
    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.5;
    fixtureDef.friction = 0.2;
    fixtureDef.restitution = 1;
    fixtureDef.shape = &polygonShape;

    initPhysical(bodyDef, fixtureDef, world, "BoxBody", "BoxFixture");

    this->m_isDrawUi = false;

    sf::Texture * boxTexture = ResourceManager::GetTexture(std::string("boxtie"));
    boxTexture->setSmooth(true);

    m_mainShape = CreateRectangleShape(b2Vec2(2, 2), boxTexture);
}

Box::~Box() {}

void Box::onFace(Person *person)
{
    printf("[Box]report box\n");
    this->m_isDrawUi = !this->m_isDrawUi;
}

void Box::DrawUiSelf()
{
    if (this->m_isDrawUi) {
        ImGui::Begin("Container");
        if (ImGui::Button("quit")) {
            this->m_isDrawUi = false;
        }
        this->DrawBoxUi(std::string("Box"));
        ImGui::End();
    } else {
        this->releaseEmptyItems();
    }
}
