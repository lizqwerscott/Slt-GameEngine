/*
 *Edit by lscott at 2018 8 19 11:18
*/

#include "PhysicalFixture.h"

using namespace slt;

PhysicalFixture::PhysicalFixture(std::string name, b2FixtureDef fixtureDef, b2Body * body)
    : Object(name), m_fixture(nullptr)
{
    for (int i = 0; i < 5; i++) {
        datas[i] = 0;
    }
    datas[0] = reinterpret_cast<uintptr_t>(this);
    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(datas);
    this->m_fixture = body->CreateFixture(&fixtureDef);
}

PhysicalFixture::~PhysicalFixture()
{
}

void PhysicalFixture::init()
{

}
