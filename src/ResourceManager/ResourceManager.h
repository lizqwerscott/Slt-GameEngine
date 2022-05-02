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
    static void init(std::string resourcePath = "");
    static void Destory();
public:
    static std::string getResourcePath();
    static void setResourcePath(std::string resourcePath);
public:
    //Texture
    static sf::Texture * LoadTextureFromFile(const std::string &fileName, const std::string &textureName);
    static sf::Texture * GetTexture(const std::string &textureName);
    static void DeleteTexture(const std::string &textureName);
    //Font
    static sf::Font * LoadFontFromFile(const std::string &fileName, const std::string &fontName);
    static sf::Font  * GetFont(const std::string &fontName);
    static void DeleteFont(const std::string &fontName);
private:
    ResourceManager();
    ~ResourceManager();
private:
    std::map<std::string, sf::Texture *> m_textures;
    std::map<std::string, sf::Font *> m_fonts;
    std::string m_resourcePath;
};
}

#endif
