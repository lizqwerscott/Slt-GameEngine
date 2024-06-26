#ifndef PHYSICALFIXTURE_H
#define PHYSICALFIXTURE_H

#include <box2d/box2d.h>
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
    b2FixtureDef m_fixtureDef;
    b2Fixture * m_fixture;
    uintptr_t datas[5];
};
}

#endif
