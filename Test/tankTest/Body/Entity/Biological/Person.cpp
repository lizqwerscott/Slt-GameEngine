#include "Person.h"
#include "../../Item/Gun/Gun.h"

Person::Person(std::string name, GameObject * parent, PhysicalWorld * world, b2Vec2 nodePos) :
    Biological(name, parent, nodePos, 100),
    m_face(b2Vec2(0, 0)),
    m_water(100),
    m_food(100)
{
    b2Vec2 localWorldPos(0, 0);
    b2BodyDef bodyDef;
    bodyDef.type = b2BodyType::b2_dynamicBody;
    bodyDef.position =
        Math::WorldCoordSToPhysicalCoordS(nodePos + localWorldPos);
    bodyDef.angle = 0;
    bodyDef.bullet = true;

    auto physicalBody = this->CreatePhysicalBody(std::string("PersonBody"), localWorldPos, bodyDef, world);

    b2CircleShape circleShape;
    // circleShape.m_p = Math::WorldCoordSToPhysicalCoordS(nodePos +
    // localWorldPos); //position, relative to body position
    circleShape.m_p = b2Vec2(0, 0);
    circleShape.m_radius = 1; // radius
    b2FixtureDef fixtureDef;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.3;
    fixtureDef.shape = &circleShape;
    fixtureDef.restitution = 1;
    auto fixture = physicalBody->CreateFixture(std::string("fixture"), fixtureDef);
    this->GetPhysicalBody()->GetBody()->GetUserData().data.push_back(static_cast<void *>(this));
    fixture->m_fixture->GetUserData().data.push_back(static_cast<void *>(this));
    m_findRayCastCallBack = new FindRayCastCallback(this);
}

Person::~Person() 
{
    if (m_tHand != nullptr) {
        delete m_tHand;
        m_tHand = nullptr;
    }
    if (m_findRayCastCallBack != nullptr) {
        delete m_findRayCastCallBack;
        m_findRayCastCallBack = nullptr;
    }
    // if (m_tBackPack != nullptr) {
    //     delete m_tBackPack;
    //     m_tHand = nullptr;
    // }
}

void Person::useHand(PhysicalWorld * world, b2Vec2 mouseClick)
{
    b2Vec2 selfPos = GetPosition();
    printf("face: %f, %f\n", m_face.x, m_face.y);
    printf("click P: %f, %f\n", mouseClick.x, mouseClick.y);
    printf("Pos: %f, %f\n", selfPos.x, selfPos.y);
    Gun * gun = static_cast<Gun *>(m_tHand);
    b2Vec2 jiPos = mouseClick - this->GetPosition();
    double cosAngle = jiPos.x / jiPos.Length();
    double sinAngel = jiPos.y / jiPos.Length();
    b2Vec2 targetPos = b2Vec2(cosAngle * 1.3, sinAngel * 1.3) + GetPosition();
    printf("bullet generate: %f, %f\n", targetPos.x, targetPos.y);
    gun->fire(this, world, targetPos);
}

Item * Person::getHand()
{
    return m_tHand;
}

void Person::useFace(PhysicalWorld * world)
{
    //find face entity;
    printf("face: %f, %f\n", m_face.x, m_face.y);
    world->RayCast(m_findRayCastCallBack, GetPosition(), m_face);
}

void Person::move()
{
}

void Person::drink(Item * drink)
{
}

void Person::eat(Item * food)
{
}

void Person::wear(Item * clothes)
{
}

bool Person::equip(Item *tool)
{
    if (m_tHand == nullptr) {
        m_tHand = tool;
        return true;
    } else {
        return false;
    }
}

void Person::UpdateSelf(sf::Time &dt)
{
    m_face = Math::DrawCoordSToPhysicalCoords(Graphic::PixelToCoords(sf::Mouse::getPosition()));
}

