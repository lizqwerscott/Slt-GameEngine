#ifndef BULLET_H
#define BULLET_H

#include "../Entity.h"

class Bullet : public Entity
{
public:
    Bullet(std::string name, GameObject * parent, PhysicalWorld * world, b2Vec2 nodePos);
public:
    void setInitSpeed(b2Vec2 speed);
};

#endif /* BULLET_H */
