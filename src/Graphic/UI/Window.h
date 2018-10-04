/*
* @Author: lscott
* @Date:   2018-06-18 17:10:50
* @Last Modified by:   lscott
* @Last Modified time: 2018-06-18 17:11:01
*/

#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <memory>

#include <SFML/Graphics.hpp>1

class Window
{
public:
    ~Window();
    Window(std::string name, int width, int height);
public:
    std::string m_name;
    std::shared_ptr<sf::RenderWindow> m_window;
};

#endif
