/*
 *Edit by lscott at 2018 8 16 16::22
 *PhysicWorld
 */
#include "PhysicalWorld.h"
#include "../Graphic/Graphic.h"

using namespace slt;

PhysicalWorld::PhysicalWorld(std::string name, bool isOpenDebugDraw, int32 vI,
                             int32 pI, b2Vec2 gravity)
    : b2World(gravity), Object(name), m_isOpenDebugDraw(isOpenDebugDraw),
      settings(new Settings()) {
  this->settings->velocityIterations = vI;
  this->settings->positionIterations = pI;
  this->SetContactListener(this);
  if (m_isOpenDebugDraw)
    this->SetDebugDraw(Graphic::getInstance());
}

PhysicalWorld::~PhysicalWorld() { delete this->settings; }

void PhysicalWorld::init() {}

void PhysicalWorld::setDebugDraw(bool isOpen) {
  this->m_isOpenDebugDraw = isOpen;
  this->SetDebugDraw(Graphic::getInstance());
}

void PhysicalWorld::Update(sf::Time &dt, b2Vec2 parentsWorldPos) {
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
    std::function<void(b2Contact *contact)> beginContact) {
  this->m_beginContact.push_back(beginContact);
}

void PhysicalWorld::onEndContact(
    std::function<void(b2Contact *contact)> endContact) {
  this->m_endContact.push_back(endContact);
}

void PhysicalWorld::onBeginContact() { this->m_beginContact.pop_back(); }

void PhysicalWorld::onEndContact() { this->m_endContact.pop_back(); }

void PhysicalWorld::BeginContact(b2Contact *contact) {
  for (auto beginContact : this->m_beginContact) {
    beginContact(contact);
  }
}

void PhysicalWorld::EndContact(b2Contact *contact) {
  for (auto endContact : this->m_endContact) {
    endContact(contact);
  }
}
