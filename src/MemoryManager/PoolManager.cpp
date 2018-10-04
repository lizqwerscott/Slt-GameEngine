/*
*Edit by lscott at 2018.8.7 18"44
 */
#include "PoolManager.h"
#include "Ref.h"
#include "AutoreleasePool.h"

using namespace slt;

PoolManager* PoolManager::s_singleInstance = nullptr;

PoolManager* PoolManager::getInstance()
{
    if (s_singleInstance == nullptr)
    {
        s_singleInstance = new PoolManager();
        // Add the first auto release pool
        new AutoreleasePool("cocos2d autorelease pool");
    }
    return s_singleInstance;
}

void PoolManager::destroyInstance()
{
    delete s_singleInstance;
    s_singleInstance = nullptr;
}

PoolManager::PoolManager()
{
    _releasePoolStack.reserve(10);
}

PoolManager::~PoolManager()
{   
    // 逐个析构所管理的AutoreleasePool对象
    while (!_releasePoolStack.empty())
    {
        AutoreleasePool* pool = _releasePoolStack.back();
        
        delete pool;
    }
}

// 加入AutoreleasePool对象指针时用的是stl::vector的push_back函数，
// 于是调用back函数就可以得到最新被加入的AutoreleasePool对象指针
AutoreleasePool* PoolManager::getCurrentPool() const
{
    return _releasePoolStack.back();
}

// 线性搜索每个被管理的AutoreleasePool，
// 每个AutoreleasePool对象再用contains函数线性搜索一遍
bool PoolManager::isObjectInPools(Ref* obj) const
{
    for (const auto& pool : _releasePoolStack)
    {
        if (pool->contains(obj))
            return true;
    }
    return false;
}

void PoolManager::push(AutoreleasePool *pool)
{
    _releasePoolStack.push_back(pool);
}

void PoolManager::pop()
{
    _releasePoolStack.pop_back();
}
