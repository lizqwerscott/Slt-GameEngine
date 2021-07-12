#ifndef GUN_H
#define GUN_H

#include "../Item.h"

class BulletI;
class GameObject;

class Gun : public Item
{
public:
    Gun(std::string name, double volume, double quality, int maxBulletN);
    ~Gun() {}
public:
    void fire(GameObject * person, PhysicalWorld * world, b2Vec2 position);
    void loadBullet(BulletI * bullet);
private:
    int m_nowBulletN;
    int m_maxBulletN;
    int m_bulletN;
};

#endif /* GUN_H */
