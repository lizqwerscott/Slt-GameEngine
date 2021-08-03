#include "Person.h"
#include "../../Item/Weapon/Gun/Gun.h"
#include "../../Item/Bag/Bag.h"
#include "../../ToolBox.h"
#include "../../Item/Tool/ArcWelding/ArcWelding.h"
#include "../../Entity/EntityFactory.h"

Person::Person(std::string name, GameObject * parent, PhysicalWorld * world, b2Vec2 nodePos) :
    Biological(name, parent, nodePos, 100),
    m_face(b2Vec2(0, 0)),
    m_SpeedAdjust(true),
    m_tHand(new ToolBox(50, 50)),
    m_water(100),
    m_food(100),
    m_world(world)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2BodyType::b2_dynamicBody;
    bodyDef.position = Math::WorldCoordSToPhysicalCoordS(nodePos);
    bodyDef.angle = 0;
    bodyDef.bullet = true;

    b2CircleShape circleShape;
    //b2PolygonShape polygonShape;

    circleShape.m_p = b2Vec2(0, 0);
    circleShape.m_radius = 1; // radius
    b2FixtureDef fixtureDef;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.3;
    fixtureDef.restitution = 1;
    //fixtureDef.shape = &polygonShape;
    fixtureDef.shape = &circleShape;
    initPhysical(bodyDef, fixtureDef, world, "PersonBody", "PersonFixture");

    m_findRayCastCallBack = new FindRayCastCallback(this);
    this->m_isDrawUi = false;

    sf::Texture * texture = ResourceManager::GetTexture(std::string("person"));
    texture->setSmooth(true);
    m_mainSprite = new sf::Sprite();
    m_mainSprite->setTexture(*texture);
    m_mainSprite->setOrigin(sf::Vector2f(15, 15));
}

Person::~Person()
{
    if (m_tHand != nullptr) {
        delete m_tHand;
        m_tHand = nullptr;
    }
    if (m_tBackPack != nullptr) {
        delete m_tBackPack;
        m_tBackPack = nullptr;
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

void Person::useHand(b2Vec2 mouseClick)
{
    if (!m_tHand->isEmpty()) {
        auto hand = getHand();
        if (hand->getTypeName() == std::string("Weapon")) {
            Weapon * weapon = static_cast<Weapon *>(hand);
            printf("weapon\n");
            weapon->attack(this, m_world);
        } else if (hand->getTypeName() == std::string("Tool")) {
            if (isInHand()) {
                Tool * tool = static_cast<Tool *>(hand);
                printf("use\n");
                tool->use(this, m_world);
            }
        } else {
            printf("another\n");
        }
    }
}

void Person::rightClick(b2Vec2 mouseClick)
{
    if (isInHand() && !m_tHand->isEmpty()) {
        auto hand = getHand();
        if (hand->getTypeName() == std::string("Weapon")) {
            //Weapon * weapon = static_cast<Weapon *>(hand);
        } else if (hand->getTypeName() == std::string("Tool")) {
            Tool * tool = static_cast<Tool *>(hand);
            tool->rightClick(this, mouseClick, m_world);
        }
    }
}

Item * Person::getHand()
{
    //return m_tHand;
    return m_tHand->getItem();
}

void Person::useFace(PhysicalWorld * world)
{
    //find face entity;
    printf("face: %f, %f\n", m_face.x, m_face.y);
    //world->RayCast(m_findRayCastCallBack, GetPosition(), m_face);
    if (m_faceEntity != nullptr) {
        if (isInHand()) {
            m_faceEntity->onFace(this);
        }
    }
}

void Person::wearBag(Bag *bag)
{
    this->m_tBackPack = bag;
}

//direction -> 0 or 1
//0 forward
//1 back
//2 left
//3 right
void Person::move(int direction, float force)
{
    b2Vec2 directionA;
    if (direction == 0) {
        directionA = m_face;
    } else if (direction == 1) {
        directionA = Math::InverseVector(m_face);
    } else {
        b2Vec3 face(m_face.x, m_face.y, 0);
        b2Vec3 k(0, 0, 1);
        b2Vec3 result = b2Cross(k, face);
        if (direction == 2) {
            directionA = b2Vec2(result.x, result.y);
        } else if (direction == 3) {
            directionA = Math::InverseVector(b2Vec2(result.x, result.y));
        }
    }
    m_physicalBody->GetBody()->ApplyLinearImpulseToCenter(Math::NumberProduct(directionA, force), true);
}

void Person::rotate(float angle)
{
    //rotate physical body
    float degreeRad = PI / 180;

    b2Body * body = m_physicalBody->GetBody();

    float bodyAngle = body->GetAngle();
    float nextAngle = bodyAngle + body->GetAngularVelocity() / 60.0;
    float totalRotation = angle - nextAngle;
    while ( totalRotation < -180 * degreeRad ) totalRotation += 360 * degreeRad;
    while ( totalRotation >  180 * degreeRad ) totalRotation -= 360 * degreeRad;
    float desiredAngularVelocity = totalRotation * 60;
    float torque = body->GetInertia() * desiredAngularVelocity / (1/60.0);
    body->ApplyTorque(torque, true);
    //rotate sprite
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
    if (m_tHand != nullptr) {
        //m_tHand = tool;
        m_tHand->addItem(tool);
        return true;
    } else {
        return false;
    }
}

void Person::DrawUiSelf()
{
    if (!m_isDrawUi) {
        if (m_tBackPack != nullptr) {
            m_tBackPack->releaseEmptyItems();
        }
    }
    auto flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings;
    ImGui::Begin("Self");
    //ImGui::BulletText("sdsa");
    if (ImGui::Button("quit")) {
        this->m_isDrawUi = false;
    }
    ImGui::Text("Status");
    if (ImGui::BeginTable("status", 2, flags)) {

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Name:");
        ImGui::TableNextColumn();
        ImGui::Text(GetName().c_str());

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("food:");
        ImGui::TableNextColumn();
        ImGui::Text(std::to_string(m_food).c_str());

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("water:");
        ImGui::TableNextColumn();
        ImGui::Text(std::to_string(m_water).c_str());
        ImGui::EndTable();
    }
    m_tHand->DrawBoxUi(std::string("Hand"));
    {
        if (!m_tHand->isEmpty()) {
            auto hand = getHand();
            if (hand != nullptr) {
                if (hand->getName() == std::string("ArcWelding")) {
                    //ImGui::Text("Create");
                    auto list = EntityFactory::getAll();
                    const char * items[list.size()];
                    Math::vectorToCharList(list, items);
                    ImGui::Combo("Create", &selectI, items, list.size());
                }
            }
        }
    }
    if (m_tBackPack != nullptr) {
        m_tBackPack->DrawBoxUi(std::string("Bag"));
    } else {
        ImGui::Text("Null");
    }
    ImGui::End();
}

void Person::UpdateSelf(sf::Time &dt)
{
    b2Vec2 mousePos = Graphic::getMousePositionP();
    m_MousePos = mousePos;
    b2Vec2 nowFace = Math::UnitVector(mousePos - GetPosition());
    float targetAngle = atan2f(-nowFace.x, nowFace.y);
    rotate(targetAngle);
    m_face = nowFace;
    //printf("m_face, %f, %f\n", m_face.x, m_face.y);
    //
    m_world->RayCast(m_findRayCastCallBack, GetPosition(), m_MousePos);

    if (m_SpeedAdjust) {
        b2Vec2 lineSpeed = this->m_physicalBody->GetBody()->GetLinearVelocity();
        m_physicalBody->GetBody()->ApplyForceToCenter(Math::NumberProduct(lineSpeed, -6), true);
    }
    if (!m_tHand->isEmpty()) {
        auto hand = getHand();
        if (hand != nullptr) {
            if (hand->getName() == std::string("ArcWelding")) {
                ArcWelding * arc = static_cast<ArcWelding *>(hand);
                auto list = EntityFactory::getAll();
                arc->m_generateEntity = list[selectI];
            }
        }
    }
}
