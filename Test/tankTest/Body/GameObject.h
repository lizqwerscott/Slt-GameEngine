#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../../../src/AllSub.h"
#include <iostream>

using namespace slt;

class GameObject : public SNode
{
public:
    GameObject(std::string name, GameObject * parent, b2Vec2 nodePos = b2Vec2(0, 0), double hp = 1);
    ~GameObject();
public:
    double getHp() {return this->m_hp;}
    void increaseHp(double setp) {m_hp = m_hp + setp;}
    void decreaseHp(double setp) {m_hp = m_hp - setp;}
    void setHp(double hp) {m_hp = hp;}
private:
    double m_hp = 0;
};

#endif /* GAMEOBJECT_H */
