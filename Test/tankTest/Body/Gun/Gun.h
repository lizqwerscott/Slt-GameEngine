#ifndef GUN_H
#define GUN_H

#include "../GameObject.h"

class Gun : public GameObject
{
public:
    Gun(std::string name, GameObject * parent, PhysicalWorld * world, b2Vec2 nodePos);
public:
    void fire(SNode * parent, PhysicalWorld * world);
private:
    int m_bulletN;
};

#endif /* GUN_H */
