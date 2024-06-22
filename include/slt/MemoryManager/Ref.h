#ifndef REF_H
#define REF_H

#include <string>

namespace slt
{
class AutoreleasePool;

class Ref
{
public:
    void retain();      // 保留。引用计数+1
    void release();     // 释放。引用计数-1
    Ref * autorelease(std::string &name); // 实现自动释放。
    unsigned int getReferenceCount() const; //被引用次数
protected:
    Ref();
public:
    virtual ~Ref();
protected:
    unsigned int _referenceCount; // 引用次数
    friend class AutoreleasePool; // 自动释放池
};
}

#endif
