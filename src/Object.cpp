/*
*Edit by lscott at 2018.8.7 18:59
*The Base class
 */

#include "slt/Object.h"

using namespace slt;

Object::Object(std::string name) : m_name(name)
{

}

Object::~Object()
{

}


std::string
slt::Object::GetName()
{
    return this->m_name;
}

bool slt::Object::GetActive()
{
    return this->m_isActive;
}

bool slt::Object::GetDraw()
{
    return this->m_isDraw;
}

bool Object::GetDrawUi()
{
    return this->m_isDrawUi;
}

void slt::Object::SetActive(bool isActive)
{
    this->m_isActive = isActive;
}

void slt::Object::SetDraw(bool isDraw)
{
    this->m_isDraw = isDraw;
}

void Object::SetDrawUi(bool isDrawUi)
{
    this->m_isDrawUi = isDrawUi;
}
