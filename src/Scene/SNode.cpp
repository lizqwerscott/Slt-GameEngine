#include "SNode.h"
#include "../Graphic/Graphic.h"
#include <cstdio>
#include "../Physical/PhysicalBody.h"

using namespace slt;

SNode::SNode(std::string name, SNode * parent)
    : Node<SNode>(parent), Object(name), m_physicalBody(nullptr), m_position(b2Vec2(0.0f, 0.0f))
{
}

SNode::~SNode()
{
    this->m_UpdateCallBacks.clear();
    this->m_DrawCallBacks.clear();
    printf("[SNode:release]");
    std::cout << this->GetName();
    this->m_sprites.clear();
    this->m_shapes.clear();
    this->deletePhysicalBody();
    printf("[SNode:Finish\n]");
}

void SNode::init()
{
}

void SNode::Update(sf::Time &dt, b2Vec2 parentsWorldPos)
{
    if (this->m_isActive) {
        {
            using namespace NodeUpdateBegin;
            EventData &eventData = EventManager::Instance()->GetEventData(E_NODEUPDATEBEGIN);
            eventData[P_TYPE] = (void *)0;
            this->SendEvent(E_NODEUPDATEBEGIN, eventData);
        }
        if (this->m_physicalBody != nullptr)
            this->m_position = this->m_physicalBody->GetPosition() - parentsWorldPos;
        this->UpdateSelf(dt);
        for (auto callBack : this->m_UpdateCallBacks) {
            callBack(this);
        }
        {
            using namespace NodeUpdateEnd;
            EventData &eventData = EventManager::Instance()->GetEventData(E_NODEUPDATEEND);
            eventData[P_TYPE] = (void *)1;
            this->SendEvent(E_NODEUPDATEEND, eventData);
        }
        //delete child
        for (auto node : m_deleteChild) {
            node->m_isActive = false;
            node->release();
            this->m_next.remove(node);
        }
        m_deleteChild.clear();
        if (this->m_isActive) {
            if (!this->m_next.empty()) {
                for (auto next : this->m_next) {
                    next->Update(dt, this->m_position + parentsWorldPos);
                }
            }
        }
    }
}

void SNode::Draw()
{
    for (auto next : this->m_next) {
        next->Draw();
    }
    if (this->m_isDraw) {
        this->DrawSelf();
        for (auto callBack : this->m_DrawCallBacks) {
            callBack(this);
        }
        for (auto sprite : this->m_sprites) {
            //const sf::Vector2f tempPos = sprite.second->getPosition();
            sprite.second->setPosition(Math::WorldCoordSToDrawCoordS(this->m_position));
            Graphic::DrawSprite(sprite.second.get());
            //sprite.second->setPosition(tempPos);
        }
        for (auto shape : this->m_shapes) {
            //const sf::Vector2f tempPos = shape.second->getPosition();
            shape.second->setPosition(Math::WorldCoordSToDrawCoordS(this->m_position));
            //printf("Shape:%s:Pos:%f, %f\n", this->GetName().c_str(), shape.second->getPosition().x, shape.second->getPosition().y);
            /*
            for (int j=0; j<shape.second->getPointCount(); j++)
            {
            	printf("Shape:%s:Pos:%f, %f\n", this->GetName().c_str(), shape.second->getPoint(j).x, shape.second->getPoint(j).y);
            }
            */
            Graphic::DrawShape(shape.second.get());
            //shape.second->setPosition(tempPos);
        }
    }
}

b2Vec2
SNode::GetPosition()
{
    return this->m_position;
}

void SNode::SetPosition(b2Vec2 pos)
{
    this->m_position = pos;
    if (this->m_physicalBody != nullptr)
        this->m_physicalBody->GetBody()->SetTransform(pos, this->m_physicalBody->GetBody()->GetAngle());
}

void SNode::move(b2Vec2 posOffset)
{
    this->SetPosition(this->m_position + posOffset);
}

SNode * SNode::GetChild(std::string name)
{
    auto iter = find_if(m_next.begin(), m_next.end(), [name](SNode * node) {
        return name == node->GetName();
    });
    if (iter != this->m_next.end()) {
        return *iter;
    } else {
        return nullptr;
    }
}

std::shared_ptr<sf::Sprite>
SNode::CreateSprite(std::string name)
{
    std::shared_ptr<sf::Sprite> sprite = std::shared_ptr<sf::Sprite>(new sf::Sprite());
    this->m_sprites[name] = sprite;
    return sprite;
}

void SNode::InsertShape(std::string name, sf::Shape * shape)
{
    this->m_shapes[name] = std::shared_ptr<sf::Shape>(shape);
}

PhysicalBody *
SNode::CreatePhysicalBody(std::string name, b2Vec2 localWorldPos, b2BodyDef bodyDef, b2World * world)
{
    this->m_physicalBody = new PhysicalBody(name, localWorldPos, bodyDef, world);
    return this->m_physicalBody;
}

std::shared_ptr<sf::Sprite>
SNode::GetSprite(std::string name)
{
    if (this->m_sprites.find(name) != this->m_sprites.end()) {
        return this->m_sprites[name];
    } else {
        printf("SNode::GetSprite()->[Warring]:Can't find sprite in snode's sprites\n");
        return nullptr;
    }
}

std::shared_ptr<sf::Shape>
SNode::GetShape(std::string name)
{
    if (this->m_shapes.find(name) != this->m_shapes.end()) {
        return this->m_shapes[name];
    } else {
        printf("SNode::GetShape()->[Warring]:Can't find shape in snode's shapes\n");
        return nullptr;
    }
}

PhysicalBody *
SNode::GetPhysicalBody()
{
    if (this->m_physicalBody == nullptr) {
        printf("[%s]SNode::GetPhysicalBody()->[Warring]:The PhyicalBody is nullptr\n", this->GetName().c_str());
        return nullptr;
    } else {
        return this->m_physicalBody;
    }
}

void SNode::deleteSprite(std::string name)
{
    this->m_sprites.erase(name);
}

void SNode::deleteShape(std::string name)
{
    this->m_shapes.erase(name);
}

void SNode::deletePhysicalBody()
{
    if (this->m_physicalBody != nullptr) {
        this->m_physicalBody->release();
    }
}

SNode *
SNode::CreateChild(std::string name, std::function<void(SNode *)> initFunction)
{
    SNode * node = new SNode(name, this);
    initFunction(node);
    node->init();
    this->m_next.push_back(node);
    return node;
}

void SNode::AddChild(SNode * node)
{
    node->init();
    this->m_next.push_back(node);
}

void SNode::DeleteChild(std::string name)
{
    SNode * node = this->GetChild(name);
    if (node != nullptr) {
        this->m_deleteChild.push_back(node);
    }
}

SNode * SNode::popChild(std::string name)
{
    SNode * node = this->GetChild(name);
    this->m_next.remove(node);
    return node;
}

void SNode::pushUpdateCallBack(std::function<void(SNode *)> updateCallBack)
{
    this->m_UpdateCallBacks.push_back(updateCallBack);
}

void SNode::pushDrawCallBack(std::function<void(SNode *)> drawCallBack)
{
    this->m_DrawCallBacks.push_back(drawCallBack);
}

void SNode::popUpdateCallBack()
{
    this->m_UpdateCallBacks.pop_back();
}

void SNode::popDrawCallBack()
{
    this->m_DrawCallBacks.pop_back();
}
