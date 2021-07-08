#ifndef POOLMANAGER_H
#define POOLMANAGER_H

#include <map>
#include <string>

namespace slt
{
class Ref;
class AutoreleasePool;

class PoolManager
{
public:
    static PoolManager* sharedPoolManager()
    {
        return getInstance();
    }
    static PoolManager* getInstance();

    static void purgePoolManager()
    {
        destroyInstance();
    }
    static void destroyInstance();

    AutoreleasePool *getPool(const std::string &name) const;

    bool isObjectInPools(Ref* obj) const;

    friend class AutoreleasePool;
private:
    PoolManager() {};
    ~PoolManager();

    void add(AutoreleasePool *pool);
    void remove(AutoreleasePool *pool);

    static PoolManager* s_singleInstance;

    // 同样用vector来存放所管理AutoreleasePool对象指针的列表
    std::map<std::string, AutoreleasePool*> _releasePoolMap;
};
}

#endif
