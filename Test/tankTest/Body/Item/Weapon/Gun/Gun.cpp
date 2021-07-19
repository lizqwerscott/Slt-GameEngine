#include "Gun.h"
#include "../../../Entity/Bullet/Bullet.h"
#include "../../../Entity/Biological/Person.h"
#include "../../Consume/BulletI/BulletI.h"

#include <cstdio>

Gun::Gun(std::string name, double volume, double quality, int maxBulletN) :
    Weapon(name, volume, quality),
    m_nowBulletN(0),
    m_maxBulletN(maxBulletN),
    m_bulletN(-1000)
{
}

Gun::~Gun()
{
}

void Gun::attack(Person *person, PhysicalWorld * world)
{
    b2Vec2 targetPos = Math::NumberProduct(person->getFace(), 1.3);
    fire(person, world, targetPos);
}

void Gun::fire(Person * person, PhysicalWorld * world, b2Vec2 position)
{
    if (m_nowBulletN == 0) {
        printf("need load bullet\n");
        return;
    }
    std::string bulletName = std::string("bullet") + std::to_string(m_bulletN);
    //b2Vec2 bulletPos = person-> + b2Vec2(0, 10.5);
    new Bullet(bulletName, person, world, position + person->GetPosition(), b2Vec2(position.x * 30, position.y * 30));
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
    printf("[LoadBullet]: %d\n", m_nowBulletN);
}


