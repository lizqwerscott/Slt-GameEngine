#include "Gyro.h"

Gyro::Gyro(std::string name, GameObject * parent, b2Vec2 size, b2Vec2 nodePos, double hp) :
    Entity(name, "Gyro", parent, nodePos, hp)
{
    this->m_isDrawUi = false;

    sf::Texture * gyro = ResourceManager::GetTexture("gyro");
    gyro->setSmooth(true);

    m_mainShape = CreateRectangleShape(size, gyro);
}

Gyro::~Gyro()
{

}
