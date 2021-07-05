#ifndef BULLET_H
#define BULLET_H

#include "../GameObject.h"

class Bullet : public GameObject
{
public:
    Bullet(std::string name, GameObject * parent, PhysicalWorld * world, b2Vec2 nodePos, b2Vec2 initSpeed);
};

#endif /* BULLET_H */
