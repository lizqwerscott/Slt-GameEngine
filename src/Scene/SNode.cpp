#include "SNode.h"
#include "../Graphic/Graphic.h"
#include <cstdio>
#include "../Physical/PhysicalBody.h"
#include "../ResourceManager/ResourceManager.h"
#include "../Log/Log.h"

using namespace slt;

unsigned int generate_id = 0;

SNode::SNode(std::string name, SNode * parent) :
    Node<SNode>(parent),
    Object(name),
    m_mainShape(nullptr),
    m_mainSprite(nullptr),
    m_physicalBody(nullptr),
    m_physicalFixture(nullptr),
    m_isGroup(false),
    m_position(b2Vec2(0.0f, 0.0f)),
    m_id(generate_id++)
{
}

SNode::~SNode()
{
    this->m_UpdateCallBacks.clear();
    this->m_DrawCallBacks.clear();
    Log::setLevel(LOG_LEVEL_INFO);
    Log::printLog("[SNode:release]");
    std::cout << this->GetName();
    this->m_sprites.clear();
    this->m_shapes.clear();
    if (m_mainShape != nullptr) {
        delete m_mainShape;
        m_mainShape = nullptr;
    }
    if (m_mainSprite != nullptr) {
        delete m_mainSprite;
        m_mainSprite = nullptr;
    }
    this->deletePhysicalBody();
    Log::printLog("[SNode:Finish]\n");
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
        sf::Vector2f pos = Math::WorldCoordSToDrawCoordS(this->m_position);
        float angle = 0;
        if (m_physicalBody != nullptr) {
            angle = Math::radToDegree(m_physicalBody->GetBody()->GetAngle());
        }
        if (m_mainSprite != nullptr) {
            m_mainSprite->setPosition(pos);
            m_mainSprite->setRotation(angle);
            Graphic::DrawSprite(m_mainSprite);
        }
        if (m_mainShape != nullptr) {
            m_mainShape->setPosition(pos);
            m_mainShape->setRotation(angle);
            Graphic::DrawShape(m_mainShape);
        }
        for (auto sprite : this->m_sprites) {
            sprite.second->setPosition(pos);
            sprite.second->setRotation(angle);
            Graphic::DrawSprite(sprite.second.get());
            //sprite.second->setPosition(tempPos);
        }
        for (auto shape : this->m_shapes) {
            shape.second->setPosition(pos);
            shape.second->setRotation(angle);
            Graphic::DrawShape(shape.second.get());
        }
    }
}

void SNode::DrawUi()
{
    if (m_isDrawUi) {
        this->DrawUiSelf();
        for (auto next : this->m_next) {
            next->DrawUi();
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

unsigned int SNode::GetId()
{
    return m_id;
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

SNode * SNode::GetChild(unsigned int id) {
    auto iter = find_if(m_next.begin(), m_next.end(), [id](SNode * node) {
        return id == node->GetId();
    });
    if (iter != m_next.end()) {
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

sf::Shape * SNode::getMainShape()
{
    return m_mainShape;
}

sf::Sprite * SNode::getMainSprite()
{
    return m_mainSprite;
}

bool SNode::changeShapeTexture(sf::Texture *texture)
{
    if (m_mainShape != nullptr) {
        m_mainShape->setTexture(texture);
    }
    return m_mainShape != nullptr;
}

bool SNode::changeSpriteTexture(sf::Texture *texture)
{
    if (m_mainSprite != nullptr) {
        m_mainSprite->setTexture(*texture);
    }
    return m_mainSprite != nullptr;
}

sf::RectangleShape *
SNode::CreateRectangleShape(b2Vec2 size, sf::Texture * texture)
{
    sf::RectangleShape * shape = new sf::RectangleShape(Math::SLTToPixel(b2Vec2(size.x * 2, size.y * 2)));
    shape->setOrigin(Math::SLTToPixel(size));
    shape->setTexture(texture);
    return shape;
}

PhysicalBody *
SNode::CreatePhysicalBody(std::string name, b2Vec2 localWorldPos, b2BodyDef bodyDef, b2World * world)
{
    this->m_physicalBody = new PhysicalBody(name, localWorldPos, bodyDef, world);
    return this->m_physicalBody;
}

bool SNode::isInGroup()
{
    return (m_physicalFixture != nullptr);
}

bool SNode::isGroupRoot()
{
    return (!isInGroup()) && m_isGroup;
}

std::shared_ptr<sf::Sprite>
SNode::GetSprite(std::string name)
{
    if (this->m_sprites.find(name) != this->m_sprites.end()) {
        return this->m_sprites[name];
    } else {
        Log::setLevel(LOG_LEVEL_WARNING);
        Log::printLog("SNode::GetSprite():Can't find sprite in snode's sprites\n");
        return nullptr;
    }
}

std::shared_ptr<sf::Shape>
SNode::GetShape(std::string name)
{
    if (this->m_shapes.find(name) != this->m_shapes.end()) {
        return this->m_shapes[name];
    } else {
        Log::setLevel(LOG_LEVEL_WARNING);
        Log::printLog("SNode::GetShape():Can't find shape in snode's shapes\n");
        return nullptr;
    }
}

PhysicalBody *
SNode::GetPhysicalBody()
{
    if (this->m_physicalBody == nullptr) {
        Log::setLevel(LOG_LEVEL_WARNING);
        Log::printLog("[%s]SNode::GetPhysicalBody():The PhyicalBody is nullptr\n", this->GetName().c_str());
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

void SNode::DeleteChild(unsigned int id)
{
    SNode * node = this->GetChild(id);
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

SNode * SNode::popChild(unsigned int id)
{
    SNode * node = this->GetChild(id);
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
