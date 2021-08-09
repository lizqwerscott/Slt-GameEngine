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


    //TODO
    if (1) {
//        auto facePos = faceEntity->GetPosition();
        //auto faceAABB = person->getFaceFixture()->GetAABB(0);

        //auto generatePos = entity->m_physicalBody->GetPosition();
        //auto generateAABB = entity->GetPhysicalBody()->GetFixture()->m_fixture->GetAABB(0);

        ////Line is facePos generatePos
        ////faceAABB
        //auto intersection = [facePos, generatePos](b2AABB * aabb) -> b2Vec2 {
        //b2Vec2 vertices[4];
        //vertices[0] = aabb->lowerBound;
        //vertices[1] = b2Vec2(aabb->upperBound.x, aabb->lowerBound.y);
        //vertices[2] = aabb->upperBound;
        //vertices[3] = b2Vec2(aabb->lowerBound.x, aabb->upperBound.y);
        ////four Pos;
        //for (int i = 0; i < 4; i++)
        //{
        //if (Math::PointInLine(vertices[i], facePos, generatePos)) {
        //return vertices[i];
        //}
        //}
        ////four line
        //for (int i = 0; i < 4; i++)
        //{
        //b2Vec2 start = vertices[i];
        //b2Vec2 end = vertices[(i + 1) % 4];
        //if (Math::LinesIntersectionP(facePos, generatePos, start, end)) {
        //return Math::LinesIntersection(facePos, generatePos, start, end);
        //}
        //}
        //return b2Vec2(0, 0);
        //};

        //b2Vec2 faceI = intersection(&faceAABB);
        //b2Vec2 generateI = intersection(&generateAABB);
        //b2Vec2 transformI = generateI - faceI;

        //Log::setLevel(LOG_LEVEL_INFO);
        //b2Vec2 lastPos = transformI + generatePos;
        //Log::printLog("[gen]:%f, %f\n", generatePos.x, generatePos.y);
        //Log::printLog("[pos]:%f, %f\n", lastPos.x, lastPos.y);
        ////entity->SetPosition(transformI + generatePos);
        //entity->m_physicalBody->GetBody()->SetTransform(transformI + generatePos, 0);
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
    if (isEquip()) {
        Person * person = static_cast<Person *>(m_equipEntity);
        auto faceFixture = person->getFaceFixture();
        if (person->isHaveSelected()) {
            auto pos = (faceFixture->GetBody()->GetPosition());
            if (person->isInSelected()) {
                auto aabb = faceFixture->GetAABB(0);
                aabb.upperBound = Math::NumberProduct(aabb.upperBound - pos, 1.1) + pos;
                aabb.lowerBound = Math::NumberProduct(aabb.lowerBound - pos, 1.1) + pos;
                Graphic::getInstance()->DrawAABB(&aabb, b2Color(219, 112, 147));
                Graphic::getInstance()->DrawPoint(pos, 1, b2Color(255, 0, 0));
            }

            auto mousePos = Graphic::getMousePositionP();
            if (mousePos.Length() - pos.Length() <= 2) {
                b2Vec2 vertices[2];
                vertices[0] = pos;
                vertices[1] = mousePos;
                Graphic::getInstance()->DrawPolygon(vertices, 2, b2Color(255, 0, 0));
            }
        }
    }
}
