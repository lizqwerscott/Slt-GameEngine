/*
* @Author: lscott
* @Date:   2018-06-18 17:31:00
* @Last Modified by:   lscott
* @Last Modified time: 2018-06-19 12:07:16
*/

#include "Renderer.h"

Renderer *render = nullptr;

void Renderer::init()
{
    render = new Renderer();
}

void Renderer::Destory()
{
    delete render;
}

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}
