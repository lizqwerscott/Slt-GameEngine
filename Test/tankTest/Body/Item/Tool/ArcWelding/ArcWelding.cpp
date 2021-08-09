#include "ArcWelding.h"
#include "../../../Entity/Biological/Person.h"
#include "../../../Entity/EntityFactory.h"

ArcWelding::ArcWelding(std::string name, double volume, double quality) :
    Tool(name, volume, quality)
{
}

void ArcWelding::use(Person *person, PhysicalWorld *world)
{
    Log::setLevel(LOG_LEVEL_INFO);
    if (person->isHaveSelected()) {
        b2Vec2 pos = person->getMousePos();
        Entity * faceEntity = person->getFaceEntity();
        Log::printLog("Together generate: %s, pos: %f, %f \n", m_generateEntity.c_str(), pos.x, pos.y);
        EntityFactory::generateEntity(m_generateEntity, pos, faceEntity);

    } else {
        b2Vec2 pos = person->getMousePos();
        Log::printLog("Alone generate: %s, pos: %f, %f \n", m_generateEntity.c_str(), pos.x, pos.y);
        EntityFactory::generateEntity(m_generateEntity, pos);
    }
}

void ArcWelding::rightClick(Person * person, b2Vec2 pos, PhysicalWorld * world)
{
    Entity * entity = person->getFaceEntity();
    b2Fixture * fixture = person->getFaceFixture();
    std::vector<b2Fixture *> m_contants = world->getContact(fixture);

    //Find the nearest body
    Entity * contantEntity = nullptr;
    b2Vec2 faceCenterPos = entity->GetPosition();
    float minLength = 10000;
    Log::setLevel(LOG_LEVEL_INFO);
    Log::printLog("facePos: %f, %f\n", faceCenterPos.x, faceCenterPos.y);
    Log::printLog("contacts:---------\n");
    for (auto item : m_contants) {
        void * userData = item->GetUserData().data[1];
        if (userData) {
            Entity * entityContant = static_cast<Entity * >(userData);
            if (entityContant != person) {
                b2Vec2 contactCenterPos = entityContant->GetPosition();
                Log::printLog("contan:%s, %f, %f\n", entityContant->GetName().c_str(), contactCenterPos.x, contactCenterPos.y);
                float length = (pos - contactCenterPos).Length();
                if (length < minLength) {
                    contantEntity = entityContant;
                    minLength = length;
                }
            }
        }
    }
    Log::printLog("contacts:---------\n");
    Log::printLog("click pos: %f, %f\n", pos.x, pos.y);
    if (contantEntity != nullptr) {
        b2Vec2 contactCenterPos = contantEntity->GetPosition();
        Log::printLog("finally min: %s, %f, %f\n", contantEntity->GetName().c_str(), contactCenterPos.x, contactCenterPos.y);
        //Contact
        b2WeldJointDef joinDef;
        joinDef.Initialize(fixture->GetBody(), contantEntity->m_physicalBody->GetBody(), b2Vec2(0, 0));
        world->CreateJoint(&joinDef);
    }
}

void ArcWelding::draw()
{
}
