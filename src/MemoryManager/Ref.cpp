/*
*Edit by lscott at 2018.8.7 10:49
*memort manager
 */

#include "Ref.h"
#include "PoolManager.h"
#include "AutoreleasePool.h"

using namespace slt;

Ref::Ref() : _referenceCount(1)
{
}

Ref::~Ref()
{
}

void Ref::retain()
{
    //CCASSERT(_referenceCount > 0, "reference count should greater than 0");
    ++_referenceCount;
}

void Ref::release()
{
    //CCASSERT(_referenceCount > 0, "reference count should greater than 0");
    --_referenceCount;
    if (_referenceCount == 0)
    {
        delete this;
    }
}

Ref * Ref::autorelease(std::string &name)
{
    // 将节点加入自动释放池
    PoolManager::getInstance()->getPool(name)->addObject(this);
    return this;
}

unsigned int 
Ref::getReferenceCount() const
{
    return this->_referenceCount;
}
