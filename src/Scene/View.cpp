#include "View.h"
#include "../Math/QuadTree.h"

using namespace slt;

View::View(sf::FloatRect range) : m_quadTree(nullptr), m_viewRange(range)
{
	this->m_quadTree = new QuadTree(this->m_viewRange);
}

View::~View()
{

}

void 
View::Update()
{
	;
}

void 
View::Draw()
{

}
