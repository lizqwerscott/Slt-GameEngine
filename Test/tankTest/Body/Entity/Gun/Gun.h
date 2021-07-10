#ifndef GUN_H
#define GUN_H

#include "../Entity.h"

class Gun : public Entity
{
public:
    Gun(std::string name, GameObject * parent, PhysicalWorld * world, b2Vec2 nodePos);
public:
    void fire(SNode * parent, PhysicalWorld * world);
private:
    int m_bulletN;
};

#endif /* GUN_H */
