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
    if (s_singleInstance == nullptr) {
        s_singleInstance = new PoolManager();
        // Add the first auto release pool
        new AutoreleasePool("main");
    }
    return s_singleInstance;
}

void PoolManager::destroyInstance()
{
    delete s_singleInstance;
    s_singleInstance = nullptr;
}

PoolManager::~PoolManager()
{
    for (auto pool : _releasePoolMap) {
        delete pool.second;
    }
}

AutoreleasePool* PoolManager::getPool(const std::string &name) const
{
    auto it = _releasePoolMap.find(name);
    if (it != _releasePoolMap.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

// 线性搜索每个被管理的AutoreleasePool，
// 每个AutoreleasePool对象再用contains函数线性搜索一遍
bool PoolManager::isObjectInPools(Ref* obj) const
{
    for (auto pool : _releasePoolMap) {
        if (pool.second->contains(obj))
            return true;
    }
    return false;
}

void PoolManager::add(AutoreleasePool *pool) {
    _releasePoolMap[pool->getName()] = pool;
}

void PoolManager::remove(AutoreleasePool *pool) {
    auto it = _releasePoolMap.find(pool->getName());
    if (it != _releasePoolMap.end()) {
        _releasePoolMap.erase(it);
    }
}

