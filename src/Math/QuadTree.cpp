#include "slt/Math/QuadTree.h"
#include "slt//Scene/SNode.h"
#include "slt/Math/QuadNode.h"

using namespace slt;

QuadTree::QuadTree(sf::FloatRect range) : Tree<QuadNode>()
{
	this->m_RootTree = new QuadNode(sf::Vector2f(0, 0), range, nullptr);
}

QuadTree::~QuadTree()
{
	delete this->m_RootTree;
	this->m_RootTree = nullptr;
}

void QuadTree::init(SNode * tree)
{
	this->insert(tree, this->m_RootTree);
}

void QuadTree::insert(SNode * snode, QuadNode *parent)
{

}
