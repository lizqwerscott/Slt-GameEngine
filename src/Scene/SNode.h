#ifndef SNODE_H
#define SNODE_H

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <functional>

#include "../Math/Node.h"
#include "../Object.h"

#include "../Math/Math.h"
#include "../Event/EventManager.h"

//Edit by lscott in 2018 7 19 21:48

namespace slt
{
class PhysicalBody;
class PhysicalFixture;

class SNode : public Node<SNode>, public Object
{
public:
    enum EventSNodeType {
        ES_UpdateBegin = 1,
        ES_UpdateEnd
    };
public:
    SNode(std::string name, SNode * parent);
    virtual ~SNode();
public:
    virtual void init() override;
    virtual void Update(sf::Time &dt, b2Vec2 parentsWorldPos) override;
    virtual void UpdateSelf(sf::Time &dt) override {}
    virtual void Draw() override;
    virtual void DrawSelf() override {}
    virtual void DrawUi() override;
    virtual void DrawUiSelf() override {};
    b2Vec2 GetPosition();
public:
    void SetPosition(b2Vec2 pos);
    void move(b2Vec2 posOffset);
public:
    std::shared_ptr<sf::Sprite> CreateSprite(std::string name);
    void InsertShape(std::string name, sf::Shape * shape);
    sf::RectangleShape * CreateRectangleShape(std::string name, b2Vec2 size, sf::Texture * texture);
    PhysicalBody * CreatePhysicalBody(std::string name, b2Vec2 localWorldPos, b2BodyDef bodyDef, b2World * world);
    bool isInGroup();
    bool isGroupRoot();

    std::shared_ptr<sf::Sprite> GetSprite(std::string name);
    std::shared_ptr<sf::Shape> GetShape(std::string name);
    PhysicalBody * GetPhysicalBody();

    void deleteSprite(std::string name);
    void deleteShape(std::string name);
    void deletePhysicalBody();
public:
    unsigned int GetId();
    SNode * GetChild(std::string name);
    SNode * GetChild(unsigned int id);
    SNode * CreateChild(std::string name, std::function<void(SNode *)> initFunction = [](SNode * node)->void {});
    void AddChild(SNode * node);
    void DeleteChild(std::string name);
    void DeleteChild(unsigned int id);
    SNode * popChild(std::string name);
    SNode * popChild(unsigned int id);
public:
    //CallBack

    void pushUpdateCallBack(std::function<void(SNode *)> updateCallBack);
    void pushDrawCallBack(std::function<void(SNode *)> drawCallBack);
    void popUpdateCallBack();
    void popDrawCallBack();
private:
    std::vector<std::function<void(SNode *)>> m_UpdateCallBacks;
    std::vector<std::function<void(SNode *)>> m_DrawCallBacks;
public:
    std::map<std::string, std::shared_ptr<sf::Sprite>> m_sprites;
    std::map<std::string, std::shared_ptr<sf::Shape>> m_shapes;
    PhysicalBody * m_physicalBody;
    PhysicalFixture * m_physicalFixture;
    bool m_isGroup;
private:
    b2Vec2 m_position;
private:
    std::list<SNode *> m_deleteChild;
    unsigned int m_id;
};

//Events
//Node Update Begin
SLT_EVENT(E_NODEUPDATEBEGIN, NodeUpdateBegin)
{
    SLT_PARAM(P_TYPE, type);
}

//Node Update End
SLT_EVENT(E_NODEUPDATEEND, NodeUpdateEnd)
{
    SLT_PARAM(P_TYPE, type);
}

}
#endif
