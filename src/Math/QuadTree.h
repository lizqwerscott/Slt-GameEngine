#ifndef QUADTREE_H
#define QUADTREE_H

#include "Tree.h"
#include <SFML/Graphics.hpp>

namespace slt
{
class QuadNode;
class SNode;
class QuadTree : public Tree<QuadNode>
{
public:
	QuadTree(sf::FloatRect range);
	~QuadTree();
public:
	void init(SNode * tree);
	void insert(SNode * snode, QuadNode * parent);
};
}

#endif
