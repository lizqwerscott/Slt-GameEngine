#ifndef ARCWELDING_H
#define ARCWELDING_H

#include "../Tool.h"

class ArcWelding : public Tool
{
public:
    ArcWelding(std::string name, double volume, double quality);
    virtual ~ArcWelding() {}
public:
    virtual void use(Person * person, PhysicalWorld * world);
    virtual void rightClick(Person * person, b2Vec2 pos, PhysicalWorld * world);
public:
    std::string m_generateEntity;
};

#endif /* ARCWELDING_H */
