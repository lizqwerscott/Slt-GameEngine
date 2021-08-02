#include "EntityFactory.h"

EntityFactory * entityFactory = nullptr;

EntityFactory::EntityFactory()
{
}

EntityFactory::~EntityFactory()
{
    m_entityMap.clear();
}

void EntityFactory::Create()
{
    if (entityFactory == nullptr) {
        entityFactory = new EntityFactory();
    }
}

void EntityFactory::Destroy()
{
    if (entityFactory != nullptr) {
        delete entityFactory;
        entityFactory = nullptr;
    }
}

void EntityFactory::addEntity(std::string name, std::function<Entity * (b2Vec2)> map)
{
    entityFactory->m_entityMap[name] = map;
}

void EntityFactory::removeEntity(std::string name)
{
    auto iter = entityFactory->m_entityMap.find(name);
    if (iter != entityFactory->m_entityMap.end()) {
        entityFactory->m_entityMap.erase(iter);
    }
}

Entity * EntityFactory::generateEntity(std::string name, b2Vec2 pos)
{
    auto iter = entityFactory->m_entityMap.find(name);
    Entity * entity = nullptr;
    if (iter != entityFactory->m_entityMap.end()) {
        entity = iter->second(pos);
    } else {
        printf("cant't find it:%s\n", name.c_str());
    }
    return entity;
}

std::vector<std::string>
EntityFactory::getAll()
{
    std::vector<std::string> result;
    for (auto iter : entityFactory->m_entityMap) {
        result.push_back(iter.first);
    }
    return result;
}

