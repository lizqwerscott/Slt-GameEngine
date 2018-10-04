//
// Created by lscott on 18-6-4.
//

#include "Brick.h"
#include <resource_manager/ResourceManager.h>
#include <Render/Renderer.h>
#include <Math/Math.h>

#include <iostream>

Brick::Brick(std::string name, b2Vec2 position, b2Vec2 size, glm::vec3 color, std::string textureName) :
        GameObject(name, ResourceManager::CreateBody(ResourceManager::CreateBodyDef(position, 0.0f, b2BodyType::b2_staticBody)), GameObjectType::o_Brick)
{
    if (ResourceManager::isHaveTexture(textureName))
    {
        std::cout << "CreateBrick:" << name << std::endl;
        std::cout << "Pos:" << position.x << ", " << position.y << std::endl;
        std::cout << "Size:" << size.x << ", " << size.y << std::endl;
        std::string spriteName = std::string(name + "_sprite");
        ResourceManager::CreateSprite(spriteName, textureName, b2Vec2(meterToPixels(size.x), meterToPixels(size.y)), color);
        ResourceManager::CreateBoxFixture(size, position, 0.0f, 0.2f, 0.5f, 0.8f, static_cast<void *>(Renderer::getSprite(spriteName).get()), this->m_body);
    }
}

Brick::~Brick() {

}

