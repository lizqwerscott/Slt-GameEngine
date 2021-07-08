/*
*Edit by lscott at 2018.8.7 18:33
*Resovle memory
*Auto releseve memory
 */
#include "AutoreleasePool.h"
#include "PoolManager.h"
#include "Ref.h"

using namespace slt;

AutoreleasePool::AutoreleasePool(std::string name) : _name(name)
{
    PoolManager::getInstance()->add(this);
}

AutoreleasePool::~AutoreleasePool()
{
    clear();

    // 要析构的AutoreleasePool对象不再由PoolManager管理
    PoolManager::getInstance()->remove(this);
}

// 只是单纯调用vector::push_back加入所管理的对象
void AutoreleasePool::addObject(Ref* object)
{
    _managedObjectArray.push_back(object);
}

// clear函数就是AutoreleasePool调用release来管理对象的引用计数的地方
void AutoreleasePool::clear()
{
    // 调用每个在AutoreleasePool的对象指针的release方法
    for (const auto &obj : _managedObjectArray) {
        if (this->_name == std::string("event")) {
            printf("obj release\n");
        }
        obj->release();
    }
    // 清空存放管理对象的vector
    _managedObjectArray.clear();
}

// 线性搜索所管理的对象指针的vector，查看所指定的Ref指针是否存在
bool AutoreleasePool::contains(Ref* object) const
{
    for (const auto& obj : _managedObjectArray) {
        if (obj == object)
            return true;
    }
    return false;
}

std::string AutoreleasePool::getName()
{
    return _name;
}

