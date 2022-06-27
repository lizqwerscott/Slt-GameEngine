#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "Entity.h"

#define factoryFun std::function<Entity * (b2Vec2 pos, Entity * mainEntity)> 

struct entityData {
    entityData(const std::string &_name, b2Vec2 _size) :
        name(_name), size(_size)
    {

    }
    b2Vec2 getSize()
    {
        b2Vec2 _size = this->size;
        if (angle == 90 || angle == 270) {
            _size = b2Vec2(size.y, size.x);
        }
        return _size;
    }
    std::string name;
    b2Vec2 size;
    int angle = 0;
    factoryFun init;
};

class EntityFactory
{
public:
    static void addEntity(entityData * entityData);
    static entityData * getEntityData(std::string name);
    static void removeEntity(std::string name);
    static Entity * generateEntity(std::string name, b2Vec2 pos, Entity * mainEntity = nullptr);
public:
    static std::vector<std::string> getAll();
public:
    static void Create();
    static void Destroy();
private:
    std::map<std::string , entityData *> m_entityMap;
private:
    EntityFactory();
    virtual ~EntityFactory();
};

#endif /* ENTITYFACTORY_H */
