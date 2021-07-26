#ifndef PHYSICALWORLD_H
#define PHYSICALWORLD_H

#include <box2d/box2d.h>
#include <SFML/System.hpp>
#include "../Object.h"
#include <functional>

namespace slt
{
/// Test settings. Some can be controlled in the GUI.
struct Settings {
    Settings()
    {
        hz = 60.0f;
        velocityIterations = 8; //how strongly to correct velocity
        positionIterations = 3; //how strongly to correct position
        drawShapes = true;
        drawJoints = true;
        drawAABBs = false;
        drawContactPoints = false;
        drawContactNormals = false;
        drawContactImpulse = false;
        drawFrictionImpulse = false;
        drawCOMs = false;
        drawStats = false;
        drawProfile = false;
        enableWarmStarting = true;
        enableContinuous = true;
        enableSubStepping = false;
        enableSleep = true;
        pause = false;
        singleStep = false;
    }

    float_t hz;
    int32 velocityIterations;
    int32 positionIterations;
    bool drawShapes;
    bool drawJoints;
    bool drawAABBs;
    bool drawContactPoints;
    bool drawContactNormals;
    bool drawContactImpulse;
    bool drawFrictionImpulse;
    bool drawCOMs;
    bool drawStats;
    bool drawProfile;
    bool enableWarmStarting;
    bool enableContinuous;
    bool enableSubStepping;
    bool enableSleep;
    bool pause;
    bool singleStep;
};

class PhysicalWorld : public b2World, public Object, public b2ContactListener
{
public:
    PhysicalWorld(std::string name, bool isOpenDebugDraw, int32 vI, int32 pI, b2Vec2 gravity);
    ~PhysicalWorld();
public:
    void setDebugDraw(bool isOpen);
public:
    virtual void init() override;
    virtual void Update(sf::Time &dt, b2Vec2 parentsWorldPos = b2Vec2(0, 0)) override;
public:
    void onBeginContact(std::function<void(b2Contact* contact)> beginContact);
    void onEndContact(std::function<void(b2Contact* contact)> endContact);
    void onBeginContact();
    void onEndContact();
public:
    //Contatct
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;
    std::vector<b2Fixture *> getContact(b2Fixture * fixture);
private:
    bool m_isOpenDebugDraw;
private:
    std::vector<std::function<void(b2Contact * contact)>> m_beginContact;
    std::vector<std::function<void(b2Contact * contact)>> m_endContact;
public:
    Settings * settings;
};
}

#endif
