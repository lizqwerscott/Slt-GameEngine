//
// Created by lscott on 18-6-5.
//

#include "Block.h"
#include <resource_manager/ResourceManager.h>
#include <Render/Renderer.h>
#include <Math/Math.h>

Block::Block(std::string name, b2Vec2 position, std::string textureName) :
        GameObject(name, ResourceManager::CreateBody(ResourceManager::CreateBodyDef(position, 0.0f, b2BodyType::b2_kinematicBody)), GameObjectType::o_Block)
{
    if (ResourceManager::isHaveTexture(textureName))
    {
        //Size /*51.2f * 2, 12.8f * 2*/
        std::string spriteName = std::string(name + "_sprite");
        ResourceManager::CreateSprite(spriteName, textureName, b2Vec2(meterToPixels(5), meterToPixels(1)), glm::vec3(1.0f));
        ResourceManager::CreateBoxFixture(b2Vec2(5.0f, 1.0f), position, 0.0f, 1.0f, 0.5f, 0.6f, static_cast<void *>(Renderer::getSprite(spriteName).get()), this->m_body);
    }
}
