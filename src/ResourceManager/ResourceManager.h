/*
* @Author: lscott
* @Date:   2018-06-18 10:14:59
* @Last Modified by:   lscott
* @Last Modified time: 2018-06-18 10:14:59
*/

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

namespace slt
{
class ResourceManager
{
public:
	static void init();
	static void Destory();
public:
	//Texture
	static sf::Texture * LoadTextureFromFile(std::string fileName, std::string textureName);
	static sf::Texture * GetTexture(std::string textureName);
	static void DeleteTexture(std::string textureName);
	//Font
	static sf::Font * LoadFontFromFile(std::string fileName, std::string fontName);
	static sf::Font  * GetFont(std::string fontName);
	static void DeleteFont(std::string fontName);
private:
    ResourceManager();
    ~ResourceManager();
private:
	std::map<std::string, sf::Texture *> m_textures;
	std::map<std::string, sf::Font *> m_fonts;
};
}

#endif
