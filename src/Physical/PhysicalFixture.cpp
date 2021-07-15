/*
 *Edit by lscott at 2018 8 19 11:18
*/

#include "PhysicalFixture.h"

using namespace slt;

PhysicalFixture::PhysicalFixture(std::string name, b2FixtureDef fixtureDef, b2Body * body)
    : Object(name), m_fixture(nullptr)
{
    fixtureDef.userData.data.push_back(this);
    this->m_fixture = body->CreateFixture(&fixtureDef);
}

PhysicalFixture::~PhysicalFixture()
{

}

void PhysicalFixture::init()
{

}

b2Fixture *
PhysicalFixture::GetFixture()
{
    return this->m_fixture;
}
