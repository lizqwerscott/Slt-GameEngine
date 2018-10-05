#ifndef PHYSICALFIXTURE_H
#define PHYSICALFIXTURE_H

#include <Box2D/Box2D.h>
#include "../Object.h"

namespace slt
{
class PhysicalFixture : public Object
{
public:
	PhysicalFixture(std::string name, b2FixtureDef fixtureDef, b2Body * body);
	~PhysicalFixture();
public:
	virtual void init() override;
public:
	b2Fixture * GetFixture();
public:
	b2Fixture * m_fixture;
};
}

#endif