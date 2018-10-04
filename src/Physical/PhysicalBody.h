#ifndef PHYSICALBODY_H
#define PHYSICALBODY_H

#include <Box2D/Box2D.h>
#include "../Object.h"
#include <memory>

namespace slt
{
class PhysicalFixture;
class PhysicalBody : public Object
{
public:
	PhysicalBody(std::string name, b2Vec2 localWorldPos, b2BodyDef bodyDef, b2World * world);
	~PhysicalBody();
public:
	virtual void init() override;
public:
	std::shared_ptr<PhysicalFixture> CreateFixture(std::string name, b2FixtureDef fixtureDef);
	void DestoryFixture(std::string name);
public:
	std::shared_ptr<PhysicalFixture> GetFixture(std::string name);
	b2Body * GetBody();
	b2Vec2 GetLocalWorldPos();
	b2Vec2 GetPosition();
private:
	b2Body * m_body;
	b2Vec2 m_localWorldPos;
	std::map<std::string, std::shared_ptr<PhysicalFixture>> m_physicalFixtures;
};
}

#endif
