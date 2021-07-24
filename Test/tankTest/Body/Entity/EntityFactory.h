#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "Entity.h"

class EntityFactory
{
public:
    static void addEntity(std::string name , std::function<Entity * (b2Vec2 pos)> map);
    static void removeEntity(std::string name);
    static Entity * generateEntity(std::string name, b2Vec2 pos);
public:
    static std::vector<std::string> getAll();
public:
    static void Create();
    static void Destroy();
private:
    std::map<std::string , std::function<Entity * (b2Vec2 pos)>> m_entityMap;
private:
    EntityFactory();
    virtual ~EntityFactory();
};

#endif /* ENTITYFACTORY_H */
