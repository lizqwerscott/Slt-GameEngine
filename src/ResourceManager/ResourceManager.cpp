/*
* @Author: lscott
* @Date:   2018-06-18 10:14:59
* @Last Modified by:   lscott
* @Last Modified time: 2018-06-18 10:15:42
*/

#include <cstdlib>
#include "ResourceManager.h"

using namespace slt;

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	for (auto texture : this->m_textures)
	{
		delete texture.second;
	}
	this->m_textures.clear();
	for (auto font : this->m_fonts)
	{
		delete font.second;
	}
	this->m_fonts.clear();
}

ResourceManager * resourceManager = nullptr;

void ResourceManager::init()
{
	resourceManager = new ResourceManager();
}

void ResourceManager::Destory()
{
	delete resourceManager;
	resourceManager = nullptr;
}

sf::Texture *
ResourceManager::LoadTextureFromFile(std::string fileName, std::string textureName)
{
	sf::Texture * texture = new sf::Texture();
	if (!texture->loadFromFile(fileName.c_str()))
	{
    printf("[ERROR]:The %s(fileName:%s) texture load error", fileName.c_str(), textureName.c_str());
	}
	resourceManager->m_textures[textureName] = texture;
	return texture;
}

sf::Texture *
ResourceManager::GetTexture(std::string textureName) {
	return resourceManager->m_textures[textureName];
}

void ResourceManager::DeleteTexture(std::string textureName)
{
	delete resourceManager->m_textures[textureName];
	resourceManager->m_textures.erase(textureName);
}

sf::Font * 
ResourceManager::LoadFontFromFile(std::string fileName, std::string fontName)
{
	sf::Font * font = new sf::Font();
	if (!font->loadFromFile(fileName.c_str()))
	{
    printf("[ERROR]:The %s(fileName:%s) font load error", fileName.c_str(), fontName.c_str());
	}
	resourceManager->m_fonts[fontName] = font;
	return font;
}

sf::Font * 
ResourceManager::GetFont(std::string fontName) {
	return resourceManager->m_fonts[fontName];
}

void ResourceManager::DeleteFont(std::string fontName)
{
	delete resourceManager->m_fonts[fontName];
	resourceManager->m_fonts.erase(fontName);
}
