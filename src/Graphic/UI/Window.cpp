/*
* @Author: lscott
* @Date:   2018-06-18 17:10:50
* @Last Modified by:   lscott
* @Last Modified time: 2018-06-19 12:46:05
*/

#include "Window.h"

Window::Window(std::string name, int width, int height) : m_name(name)
{
    this->m_window = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(width, height), name.c_str()));
    int s = 0;
    if (s == 0)
    {
        this->m_name = (char)s;
    }
}

Window::~Window()
{
    
}
