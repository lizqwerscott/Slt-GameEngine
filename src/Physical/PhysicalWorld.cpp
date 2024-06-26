/*
 *Edit by lscott at 2018 8 16 16::22
 *PhysicWorld
 */
#include "slt/Physical/PhysicalWorld.h"
#include "slt/Graphic/Graphic.h"
#include "slt/Physical/PhysicalBody.h"
#include "slt/Physical/PhysicalFixture.h"
#include "slt/Log/Log.h"
#include "slt/Math/Math.h"

using namespace slt;

PhysicalWorld::PhysicalWorld(std::string name, bool isOpenDebugDraw, int32 vI,
                             int32 pI, b2Vec2 gravity)
    : b2World(gravity), Object(name), m_isOpenDebugDraw(isOpenDebugDraw),
      settings(new Settings())
{
    this->settings->velocityIterations = vI;
    this->settings->positionIterations = pI;
    this->SetContactListener(this);
    if (m_isOpenDebugDraw) {
        this->SetDebugDraw(Graphic::getInstance());
    }
}

PhysicalWorld::~PhysicalWorld()
{
    delete this->settings;
}

void PhysicalWorld::init() {}

b2BodyDef PhysicalWorld::generateBodyDef(b2Vec2 pos, float angle, bool bullet, b2BodyType type)
{
    b2BodyDef bodyDef;
    bodyDef.type = type;
    bodyDef.position = pos;
    bodyDef.angle = angle;
    bodyDef.bullet = bullet;
    return bodyDef;
}

b2FixtureDef PhysicalWorld::generateFixtureDef(b2Shape *shape, float density, float friction, float restitution, bool isSensor)
{
    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;
    return fixtureDef;
}

b2Vec2 PhysicalWorld::generateNodePos(PhysicalBody * body, b2Vec2 bodySize, b2Vec2 size)
{
    b2Vec2 nodePos;
    float faceBodyAngle = body->GetBody()->GetAngle();
    b2Vec2 mainPos = body->GetPosition();

    b2Vec2 mousePos = Graphic::getMousePositionP();

    float width = bodySize.x;
    float height = bodySize.y;

    b2Vec2 v = mousePos - mainPos;
    float mAngle;
    mAngle = acos(v.x / v.Length());
    if (v.y <= 0) {
        mAngle = (PI - mAngle) + PI;
    }

    // Log::setLevel(LOG_LEVEL_INFO);
    // Log::printLog("----------------------\n");
    // Log::printLog("upperBound, %f, %f\n", width, height);
    // Log::printLog("Size, %f, %f\n", size.x, size.y);
    // Log::printLog("MainPos:%f, %f\n", mainPos.x, mainPos.y);
    // Log::printLog("v: %f, %f\n", v.x, v.y);
    // Log::printLog("mAngle:%f degree\n", Math::radToDegree(mAngle));
    // Log::printLog("faceBodyAngle:%f\n", faceBodyAngle);

    float distance = 0;
    float rightUp = (PI / 4) + faceBodyAngle;
    float leftUp = rightUp + (PI / 2);
    float leftDown = leftUp + (PI / 2);
    float rightDown = leftDown + (PI / 2);

    float mouseWidth = 0;
    float radWidth = abs(bodySize.x - size.x) / (PI / 4);
    float mouseHeight = 0;
    float radHeight = abs(bodySize.y - size.y) / (PI / 4);
    // in entity right
    if (mAngle >= rightDown || mAngle <= rightUp) {
        // Log::printLog("Right=====\n");
        distance = width + size.x;
        if (abs(size.y - height) > 0.1) {
            float runAngle = 0;
            if (mAngle >= rightDown) {
                runAngle = mAngle - rightDown;
            } else {
                runAngle = mAngle;
            }
            mouseHeight = radHeight * runAngle - size.y;
        }
        nodePos = mainPos + b2Vec2(distance, mouseHeight);
    }
    //in entity up
    if (mAngle > rightUp && mAngle <= leftUp) {
        // Log::printLog("Up=====\n");
        distance = height + size.y;
        if (abs(size.x - width) > 0.1) {
            float runAngle = leftUp - mAngle;
            mouseWidth = radWidth * runAngle - size.x;
        }
        nodePos = mainPos + b2Vec2(mouseWidth, distance);
    }
    //in entity left
    if (mAngle > leftUp && mAngle <= leftDown) {
        // Log::printLog("Left=====\n");
        distance = width + size.x;
        // Log::printLog("width: %f, %f, %f\n", width, size.x, distance);
        if (abs(size.y - height) > 0.1) {
            float runAngle = leftDown - mAngle;
            mouseHeight = radHeight * runAngle - size.y;
        }
        nodePos = mainPos + b2Vec2(-distance, mouseHeight);
    }
    //in entity down
    if (mAngle > leftDown && mAngle < rightDown) {
        // Log::printLog("Down=====\n");
        distance = height + size.y;
        if (abs(size.x - width) > 0.1) {
            float runAngle = mAngle - leftDown;
            mouseWidth = radWidth * runAngle - size.x;
        }
        nodePos = mainPos + b2Vec2(mouseWidth, -distance);
    }

    // Log::printLog("NodePos:%f, %f\n", nodePos.x, nodePos.y);
    //Calculate the coordinates rotating object after.
    b2Vec2 newNode = Math::rotatingVector(nodePos, -faceBodyAngle, mainPos);
    // Log::printLog("NewPos:%f, %f\n", newNode.x, newNode.y);
    return newNode;
}

void PhysicalWorld::setDebugDraw(bool isOpen)
{
    this->m_isOpenDebugDraw = isOpen;
    this->SetDebugDraw(Graphic::getInstance());
}

void PhysicalWorld::Update(sf::Time &dt, b2Vec2 parentsWorldPos)
{
    if (m_isOpenDebugDraw) {
        uint32 flags = 0;
        flags += settings->drawShapes * b2Draw::e_shapeBit;
        flags += settings->drawJoints * b2Draw::e_jointBit;
        flags += settings->drawAABBs * b2Draw::e_aabbBit;
        flags += settings->drawCOMs * b2Draw::e_centerOfMassBit;
        Graphic::getInstance()->SetFlags(flags);
        this->DebugDraw();
    }
    // printf("Dt:%fs\n", dt.asSeconds());
    this->Step(dt.asSeconds(), this->settings->velocityIterations,
               this->settings->positionIterations);
}

void PhysicalWorld::onBeginContact(
    std::function<void(b2Contact *contact)> beginContact)
{
    this->m_beginContact.push_back(beginContact);
}

void PhysicalWorld::onEndContact(
    std::function<void(b2Contact *contact)> endContact)
{
    this->m_endContact.push_back(endContact);
}

std::vector<b2Fixture *>
PhysicalWorld::getContact(b2Fixture *fixture)
{
    std::vector<b2Fixture *> results;
    for (b2Contact * c = this->GetContactList(); c; c = c->GetNext()) {
        b2Fixture * fixtureA = c->GetFixtureA();
        b2Fixture * fixtureB = c->GetFixtureB();
        if (fixtureA == fixture) {
            results.push_back(fixtureB);
        } else if (fixtureB == fixture) {
            results.push_back(fixtureA);
        }
    }
    return results;
}

void PhysicalWorld::onBeginContact()
{
    this->m_beginContact.pop_back();
}

void PhysicalWorld::onEndContact()
{
    this->m_endContact.pop_back();
}

void PhysicalWorld::BeginContact(b2Contact *contact)
{
    try {
        for (auto beginContact : this->m_beginContact) {
            beginContact(contact);
        }

    } catch (const std::exception& e) {
        Log::setLevel(LOG_LEVEL_ERROR);
        Log::printLog("BeginContact received a null contact pointer\n");
    }

}

void PhysicalWorld::EndContact(b2Contact *contact)
{
    try {
        for (auto endContact : this->m_endContact) {
            endContact(contact);
        }
    } catch (const std::exception& e) {
        Log::setLevel(LOG_LEVEL_ERROR);
        Log::printLog("EndContact received a null contact pointer\n");
    }
}
