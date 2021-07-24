#include "ArcWelding.h"
#include "../../../Entity/Biological/Person.h"
#include "../../../Entity/EntityFactory.h"

ArcWelding::ArcWelding(std::string name, double volume, double quality) :
    Tool(name, volume, quality)
{
}

void ArcWelding::use(Person *person, PhysicalWorld *world)
{
    if (person->isInHand()) {
        b2Vec2 pos = person->getMousePos();
        printf("generate: %s, pos: %f, %f \n", m_generateEntity.c_str(), pos.x, pos.y);
        EntityFactory::generateEntity(m_generateEntity, pos);

    }
}

void ArcWelding::rightClick()
{
}
