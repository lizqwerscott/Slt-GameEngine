/*
* @Author: lscott
* @Date:   2018-06-18 17:31:00
* @Last Modified by:   lscott
* @Last Modified time: 2018-06-18 17:31:09
*/

#ifndef RENDERER_H
#define RENDERER_H

#include <string>

class Window;

class Renderer
{
public:
    static void init();
    static void Destory();
private:
    Renderer();
    ~Renderer();
};

#endif
