/*
* @Author: lscott
* @Date:   2018-06-18 09:29:56
* @Last Modified by:   lscott
* @Last Modified time: 2018-06-18 17:01:19
*/

#include "Scene.h"
#include <iostream>
#include "../Graphic/Graphic.h"
#include "SNode.h"
#include "../Physical/PhysicalWorld.h"

using namespace slt;

Scene::Scene(std::string name, sf::FloatRect range, bool isActive) 
	: Tree<SNode>(), Object(name), m_loadRange(range), m_physicalWorld(nullptr)
{
	this->SetActive(isActive);
	this->SetDraw(true);
	this->m_RootTree = new SNode("RootSNode", nullptr);
}

Scene::~Scene()
{	
	delete this->m_RootTree;
	this->m_RootTree = nullptr;
}

void Scene::SetRange(sf::FloatRect range) {
	this->m_loadRange = range;
}

sf::FloatRect
Scene::GetRange() {
	return this->m_loadRange;
}

void Scene::Update(sf::Time &dt, b2Vec2 parentsWorldPos)
{
	if (this->m_physicalWorld != nullptr)
	{
		this->m_physicalWorld->Update(dt);
		/*
		//int count = int((1 / this->m_physicalWorld->settings->hz) / dt.asSeconds());
		int count = 1;
		for (int i=0; i<count; i++)
		{
			this->m_physicalWorld->Update(dt);
		}
		*/
	}
	this->UpdateSelf(dt);
	for (auto callback : this->m_UpdateCallBacks)
	{
		callback(this);
	}
	if (this->m_isActive)
	{
		this->m_RootTree->Update(dt, parentsWorldPos);
	}
}

void Scene::Draw()
{
	this->DrawSelf();
	for (auto callback : this->m_DrawCallBacks)
	{
		callback(this);
	}
	if (this->m_isDraw)
	{
		this->m_RootTree->Draw();
	}
}

std::shared_ptr<PhysicalWorld>
Scene::CreatePhysicalWorld(std::string name, bool isOpenDebugDraw, b2Vec2 gravity, int32 vI, int32 pI) {
	this->m_physicalWorld = std::shared_ptr<PhysicalWorld>(new PhysicalWorld(name, isOpenDebugDraw, vI, pI, gravity));
	return this->m_physicalWorld;
}

void Scene::DeletePhysicalWorld()
{
	this->m_physicalWorld->release();
}

std::shared_ptr<PhysicalWorld>
Scene::GetPhysicalWorld() {
	return this->m_physicalWorld;
}

void Scene::pushUpdateCallBack(std::function<void(Scene *)> updateCallBack) {
	this->m_UpdateCallBacks.push_back(updateCallBack);
}

void Scene::pushDrawCallBack(std::function<void(Scene *)> drawCallBack) {
	this->m_DrawCallBacks.push_back(drawCallBack);
}

void Scene::popUpdateCallBack() {
	this->m_UpdateCallBacks.pop_back();
}

void Scene::popDrawCallBack() {
	this->m_DrawCallBacks.pop_back();
}

