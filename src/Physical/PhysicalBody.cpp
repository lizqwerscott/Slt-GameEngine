/*
 *Edit by lscott at 2018 8 18 12:32
 *
*/

#include "PhysicalBody.h"
#include "../Math/Math.h"
#include "PhysicalFixture.h"
#include "../Log/Log.h"

using namespace slt;

PhysicalBody::PhysicalBody(std::string name, b2Vec2 localWorldPos, b2BodyDef bodyDef, b2World * world)
    : Object(name), m_body(nullptr), m_localWorldPos(localWorldPos)
{
    //Create Body
    this->m_body = world->CreateBody(&bodyDef);
    for (int i = 0; i < 5; i++) {
        datas[i] = 0;
    }
    datas[0] = reinterpret_cast<uintptr_t>(this);
    m_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(datas);
}

PhysicalBody::~PhysicalBody()
{
    this->m_physicalFixtures.clear();
    b2World * world = this->m_body->GetWorld();
    world->DestroyBody(this->m_body);
    world = nullptr;
    m_body = nullptr;
}

void PhysicalBody::init()
{

}

std::shared_ptr<PhysicalFixture>
PhysicalBody::CreateFixture(std::string name, b2FixtureDef fixtureDef)
{
    auto fixture = std::shared_ptr<PhysicalFixture>(new PhysicalFixture(name, fixtureDef, this->m_body));
    this->m_physicalFixtures[name] = fixture;
    return fixture;
}

void PhysicalBody::DestoryFixture(std::string name)
{
    auto physicalFixture = this->GetFixture(name);
    if (physicalFixture != nullptr) {
        physicalFixture->release();
    }
}

std::shared_ptr<PhysicalFixture>
PhysicalBody::GetFixture(std::string name)
{
    if (this->m_physicalFixtures.find(name) == this->m_physicalFixtures.end()) {
        Log::setLevel(LOG_LEVEL_ERROR);
        Log::printLog("PhyscialBody::GetFixture()->[Error:]Can't find fixture. Name:%s\n", name.c_str());
        return nullptr;
    } else {
        return this->m_physicalFixtures[name];
    }
}

std::shared_ptr<PhysicalFixture>
PhysicalBody::GetFixture()
{
    if (m_physicalFixtures.size() == 1) {
        for (auto item : m_physicalFixtures) {
            return item.second;
            break;
        }
    }
    return nullptr;
}

b2Body *
PhysicalBody::GetBody()
{
    return this->m_body;
}

b2Vec2
PhysicalBody::GetLocalWorldPos()
{
    return this->m_localWorldPos;
}

b2Vec2
PhysicalBody::GetPosition()
{
    return  Math::PhysicalCoordSToWorldCoordS(this->m_body->GetPosition()) + this->m_localWorldPos;
}
