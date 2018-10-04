#ifndef POOLMANAGER_H
#define POOLMANAGER_H

#include <vector>

namespace slt
{
class Ref;
class AutoreleasePool;

class PoolManager
{
public:
	static PoolManager* sharedPoolManager() { return getInstance(); }
    static PoolManager* getInstance();

	static void purgePoolManager() { destroyInstance(); }
    static void destroyInstance();
    
    AutoreleasePool *getCurrentPool() const;

    bool isObjectInPools(Ref* obj) const;

	friend class AutoreleasePool;
private:
	PoolManager();
	~PoolManager();
	
	void push(AutoreleasePool *pool);
    void pop();
    
    static PoolManager* s_singleInstance;
    
    // 同样用vector来存放所管理AutoreleasePool对象指针的列表
    std::vector<AutoreleasePool*> _releasePoolStack;
};
}

#endif
