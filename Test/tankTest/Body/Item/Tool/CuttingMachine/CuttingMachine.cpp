#include "CuttingMachine.h"
#include "../../../Entity/Biological/Person.h"

CuttingMachine::CuttingMachine(std::string name, double volume, double quality) :
    Tool(name, volume, quality)
{
}

void CuttingMachine::use(Person *person, PhysicalWorld *world)
{
    Entity * entity = person->getFaceEntity();
    printf("delete entity:%s, %u \n", entity->GetName().c_str(), entity->GetId());
    entity->setHp(0);
}

void CuttingMachine::rightClick(Person *person, b2Vec2 pos, PhysicalWorld *world)
{
    Entity * entity = person->getFaceEntity();
    b2Body * body = person->getFaceFixture()->GetBody();

    //Find the nearest body
    b2Joint * joint = nullptr;
    Entity * contantEntity = nullptr;
    b2Vec2 faceCenterPos = entity->GetPosition();
    float minLength = 10000;
    printf("facePos: %f, %f\n", faceCenterPos.x, faceCenterPos.y);
    printf("joint:---------\n");
    for (b2JointEdge * j = body->GetJointList(); j; j = j->next) {
        void * userData = j->other->GetUserData().data[1];
        if (userData) {
            Entity * entityContant = static_cast<Entity * >(userData);
            if (entityContant != person) {
                b2Vec2 contactCenterPos = entityContant->GetPosition();
                printf("joint:%s, %f, %f\n", entityContant->GetName().c_str(), contactCenterPos.x, contactCenterPos.y);
                float length = (pos - contactCenterPos).Length();
                if (length < minLength) {
                    contantEntity = entityContant;
                    minLength = length;
                    joint = j->joint;
                }
            }
        }
    }
    printf("joint:---------\n");
    printf("click pos: %f, %f\n", pos.x, pos.y);

    if (contantEntity != nullptr && joint != nullptr) {
        b2Vec2 contactCenterPos = contantEntity->GetPosition();
        printf("finally min: %s, %f, %f\n", contantEntity->GetName().c_str(), contactCenterPos.x, contactCenterPos.y);
        //Delete contact
        world->DestroyJoint(joint);
    }
}

