/*
 * @Author: lscott
 * @Date:   2018-06-18 09:29:56
 * @Last Modified by:   lscott
 * @Last Modified time: 2018-06-18 17:01:19
 */

#include "Scene.h"
#include "../Graphic/Graphic.h"
#include "../Physical/PhysicalWorld.h"
#include "../Graphic/Camera.h"
#include "SNode.h"
#include <iostream>

using namespace slt;

Scene::Scene(std::string name, sf::FloatRect range, bool isActive)
    : Tree<SNode>(), Object(name), m_loadRange(range),
      m_physicalWorld(nullptr)
{
    this->SetActive(isActive);
    this->SetDraw(true);
    this->m_RootTree = new SNode("RootSNode", nullptr);
    sf::Vector2u windowSize = Graphic::getWindowSize();
    auto camera = new Camera(std::string("Main"), sf::FloatRect(0.f, 0.f, windowSize.x, windowSize.y));
    this->m_cameras[std::string("Main")] = std::shared_ptr<Camera>(camera);
}

Scene::~Scene()
{
    delete this->m_RootTree;
    this->m_RootTree = nullptr;
}

void Scene::SetRange(sf::FloatRect range)
{
    this->m_loadRange = range;
}

sf::FloatRect Scene::GetRange()
{
    return this->m_loadRange;
}

void Scene::Update(sf::Time &dt, b2Vec2 parentsWorldPos)
{
    if (this->m_physicalWorld != nullptr) {
        this->m_physicalWorld->Update(dt);
        /*
        //int count = int((1 / this->m_physicalWorld->settings->hz) /
        dt.asSeconds()); int count = 1; for (int i=0; i<count; i++)
        {
                this->m_physicalWorld->Update(dt);
        }
        */
    }
    this->UpdateSelf(dt);
    for (auto camera : this->m_cameras) {
        camera.second.get()->UpdateSelf(dt);
    }
    for (auto callback : this->m_UpdateCallBacks) {
        callback(this);
    }
    if (this->m_isActive) {
        this->m_RootTree->Update(dt, parentsWorldPos);
    }
}

void Scene::Draw()
{
    for (auto camera : this->m_cameras) {
        camera.second.get()->DrawSelf();
    }
    this->DrawSelf();
    for (auto callback : this->m_DrawCallBacks) {
        callback(this);
    }
    if (this->m_isDraw) {
        this->m_RootTree->Draw();
    }
}

void Scene::DrawUi()
{
    this->DrawUiSelf();
    if (this->m_isDrawUi) {
        if (m_RootTree != nullptr) {
            this->m_RootTree->DrawUi();
        }
    }
}

std::shared_ptr<PhysicalWorld> Scene::CreatePhysicalWorld(std::string name,
        bool isOpenDebugDraw,
        b2Vec2 gravity,
        int32 vI, int32 pI)
{
    this->m_physicalWorld = std::shared_ptr<PhysicalWorld>(
                                new PhysicalWorld(name, isOpenDebugDraw, vI, pI, gravity));
    return this->m_physicalWorld;
}

void Scene::DeletePhysicalWorld()
{
    this->m_physicalWorld->release();
}

std::shared_ptr<PhysicalWorld> Scene::GetPhysicalWorld()
{
    return this->m_physicalWorld;
}

void Scene::pushUpdateCallBack(std::function<void(Scene *)> updateCallBack)
{
    this->m_UpdateCallBacks.push_back(updateCallBack);
}

void Scene::pushDrawCallBack(std::function<void(Scene *)> drawCallBack)
{
    this->m_DrawCallBacks.push_back(drawCallBack);
}

void Scene::popUpdateCallBack()
{
    this->m_UpdateCallBacks.pop_back();
}

void Scene::popDrawCallBack()
{
    this->m_DrawCallBacks.pop_back();
}
