/*
* @Author: lscott
* @Date:   2018-06-18 10:14:59
* @Last Modified by:   lscott
* @Last Modified time: 2018-06-18 10:15:42
*/

#include <cstdlib>
#include "ResourceManager.h"
#include "../Log/Log.h"

using namespace slt;

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
    for (auto texture : this->m_textures) {
        delete texture.second;
    }
    this->m_textures.clear();
    for (auto font : this->m_fonts) {
        delete font.second;
    }
    this->m_fonts.clear();
}

ResourceManager * resourceManager = nullptr;

void ResourceManager::init(std::string resourcePath)
{
    resourceManager = new ResourceManager();
    resourceManager->m_resourcePath = resourcePath;
}

void ResourceManager::Destory()
{
    delete resourceManager;
    resourceManager = nullptr;
}

std::string ResourceManager::getResourcePath()
{
    return resourceManager->m_resourcePath;
}

void ResourceManager::setResourcePath(std::string resourcePath)
{
    resourceManager->m_resourcePath = resourcePath;
}

sf::Texture *
ResourceManager::LoadTextureFromFile(const std::string &fileName, const std::string &textureName)
{
    std::string filePath = resourceManager->m_resourcePath + std::string("texture/") + fileName;
    sf::Texture * texture = new sf::Texture();
    if (!texture->loadFromFile(filePath.c_str())) {
        Log::setLevel(LOG_LEVEL_INFO);
        Log::printLog("[ERROR]:The %s(fileName:%s) texture load error\n", fileName.c_str(), textureName.c_str());
    }
    resourceManager->m_textures[textureName] = texture;
    return texture;
}

sf::Texture *
ResourceManager::GetTexture(const std::string &textureName)
{
    return resourceManager->m_textures[textureName];
}

void ResourceManager::DeleteTexture(const std::string &textureName)
{
    delete resourceManager->m_textures[textureName];
    resourceManager->m_textures.erase(textureName);
}

sf::Font *
ResourceManager::LoadFontFromFile(const std::string &fileName, const std::string &fontName)
{
    std::string filePath = resourceManager->m_resourcePath + std::string("font/") + fileName;
    sf::Font * font = new sf::Font();
    if (!font->loadFromFile(filePath.c_str())) {
        Log::setLevel(LOG_LEVEL_ERROR);
        Log::printLog("[ERROR]:The %s(fileName:%s) font load error\n", fileName.c_str(), fontName.c_str());
    }
    resourceManager->m_fonts[fontName] = font;
    return font;
}

sf::Font *
ResourceManager::GetFont(const std::string &fontName)
{
    return resourceManager->m_fonts[fontName];
}

void ResourceManager::DeleteFont(const std::string &fontName)
{
    delete resourceManager->m_fonts[fontName];
    resourceManager->m_fonts.erase(fontName);
}
