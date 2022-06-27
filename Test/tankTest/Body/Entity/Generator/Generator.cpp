#include "Generator.h"

Generator::Generator(std::string name, GameObject * parent, b2Vec2 size, b2Vec2 nodePos, double hp) :
    Entity(name, "Generator", parent, nodePos, hp)
{
    this->m_isDrawUi = false;

    sf::Texture * generatorTexture = ResourceManager::GetTexture(std::string("generator"));
    generatorTexture->setSmooth(true);

    m_mainShape = CreateRectangleShape(size, generatorTexture);
}

