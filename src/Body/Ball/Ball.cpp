//
// Created by lscott on 18-6-4.
//

#include "Ball.h"
#include <resource_manager/ResourceManager.h>
#include <Math/Math.h>
#include <Render/Renderer.h>

#include <iostream>

Ball::Ball(std::string name, b2Vec2 position, std::string textureName) :
        GameObject(name, ResourceManager::CreateBody(ResourceManager::CreateBodyDef(position, 0.0f, b2BodyType::b2_dynamicBody)), GameObjectType::o_Ball)
{
    std::string spriteName = std::string(name + "_sprite");
    ResourceManager::CreateSprite(spriteName, textureName, b2Vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.2f, 1.0f));
    ResourceManager::CreateCircleFixture(position, 1.0f, 0.5f, 0.5f, 0.9f, static_cast<void *>(Renderer::getSprite(spriteName).get()), this->m_body);
}

Ball::~Ball() {

}
