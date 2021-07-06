#ifndef QUADNODE_H
#define QUADNODE_H

#include <SFML/Graphics.hpp>
#include <list>

namespace slt
{
class SNode;
class QuadNode
{
public:
    QuadNode(sf::Vector2f pos, sf::FloatRect range, QuadNode * parent);
    ~QuadNode();
private:
    QuadNode * m_parent = nullptr;
    QuadNode * m_Children[4];
private:
    sf::Vector2f m_pos;
    sf::FloatRect m_range;
    std::list<SNode *> m_node;
};
}

#endif
