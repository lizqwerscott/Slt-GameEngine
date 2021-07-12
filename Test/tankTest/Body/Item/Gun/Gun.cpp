#include "Gun.h"
#include "../../Entity/Bullet/Bullet.h"
#include "../../GameObject.h"
#include "BulletI.h"

#include <cstdio>

Gun::Gun(std::string name, double volume, double quality, int maxBulletN) :
    Item(name, volume, quality),
    m_nowBulletN(0),
    m_maxBulletN(maxBulletN),
    m_bulletN(-1000)
{
}

void Gun::fire(GameObject * person, PhysicalWorld * world, b2Vec2 position)
{
    if (m_nowBulletN == 0) {
        printf("need load bullet\n");
        return;
    }
    std::string bulletName = std::string("bullet") + std::to_string(m_bulletN);
    //b2Vec2 bulletPos = person-> + b2Vec2(0, 10.5);
    new Bullet(bulletName, person, world, position, b2Vec2(position.x * 30, position.y * 30));
    printf("[CreateBullet]:%s, pos:%f,%f\n", bulletName.c_str(), position.x, position.y);
    m_bulletN++;
    m_nowBulletN--;
}

void Gun::loadBullet(BulletI *bullet)
{
    if (m_nowBulletN == m_maxBulletN) {
        return;
    }
    delete bullet;
    m_nowBulletN++;
    printf("[LoadBuller]: %d\n", m_nowBulletN);
}


