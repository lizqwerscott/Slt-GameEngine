#include "Engine.h"

#include "../Graphic/Graphic.h"
#include "../Scene/SceneManager.h"
#include "../ResourceManager/ResourceManager.h"
#include "../Scene/Scene.h"
#include "../MemoryManager/PoolManager.h"
#include "../MemoryManager/AutoreleasePool.h"
#include "../Math/Math.h"

using namespace slt;

Engine::Engine()
{
	ResourceManager::init();
	SceneManager::init();
}

Engine::~Engine()
{
	SceneManager::Destory();
	Graphic::Destory();
	ResourceManager::Destory();
	PoolManager::destroyInstance();
	Math::Destory();
}

int Engine::Run(sf::Time &dt)
{
	SceneManager::GetRunScene()->Update(dt);

	Graphic::Clear();
	SceneManager::GetRunScene()->Draw();
	Graphic::Render();
	Graphic::Display();

	PoolManager::getInstance()->getCurrentPool()->clear();
  //printf("The Engine dalate time:%f\n", dt.asSeconds()); 
	return 0;
}

bool Engine::isClose()
{
	return Graphic::isOpen();
}
