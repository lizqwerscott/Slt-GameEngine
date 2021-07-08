#ifndef AUTORELEASEPOOL_H
#define AUTORELEASEPOOL_H

#include <vector>
#include <string>

namespace slt
{
class Ref;

class AutoreleasePool
{
public:
    AutoreleasePool(std::string name);
    ~AutoreleasePool();
public:
    void addObject(Ref *object);
    void clear();
    bool contains(Ref* object) const;
public:
    std::string getName();
private:
    std::vector<Ref*> _managedObjectArray;
    std::string _name;
};
}

#endif
