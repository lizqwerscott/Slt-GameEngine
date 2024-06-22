#include "slt/Engine/Engine.h"

#include "slt/Graphic/Graphic.h"
#include "slt/Scene/SceneManager.h"
#include "slt/ResourceManager/ResourceManager.h"
#include "slt/Scene/Scene.h"
#include "slt/MemoryManager/PoolManager.h"
#include "slt/MemoryManager/AutoreleasePool.h"
#include "slt/Math/Math.h"
#include "slt/Log/Log.h"
#include "slt/Script/Script.h"

using namespace slt;

Engine::Engine()
{
    ResourceManager::init();
    SceneManager::init();
    Log::Create();
    Script::Create();
}

Engine::~Engine()
{
    SceneManager::Destory();
    Graphic::Destory();
    ResourceManager::Destory();
    PoolManager::destroyInstance();
    Math::Destory();
    Log::Destory();
    Script::Destory();
}

int Engine::Run(sf::Time &dt)
{
    SceneManager::GetRunScene()->Update(dt);

    Graphic::Update(dt);
    Log::drawUi();
    Script::drawUi();
    SceneManager::GetRunScene()->DrawUi();
    Graphic::Clear();
    SceneManager::GetRunScene()->Draw();
    Graphic::Render();
    Graphic::Display();

    PoolManager::getInstance()->getPool("main")->clear();
    //printf("The Engine dalate time:%f\n", dt.asSeconds());
    return 0;
}

bool Engine::isClose()
{
    return Graphic::isOpen();
}
