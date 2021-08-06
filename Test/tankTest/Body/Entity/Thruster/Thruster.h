#ifndef THRUSTER_H
#define THRUSTER_H

#include "../Entity.h"

class Thruster : public Entity
{
public:
    Thruster(std::string name, GameObject * parent, PhysicalWorld * world, b2Vec2 size, float maxThrust, b2Vec2 nodePos = b2Vec2(0, 0), double hp = 90);
    virtual ~Thruster() {}
public:
    void increaseThrust(float step = 2);
    void decreaseThrust(float step = 2);
    void push();
public:
    virtual void onFace(Person * person) {}
private:
    float m_thrust;
    float m_maxThrust;
};

#endif /* THRUSTER_H */
