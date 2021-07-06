#include "QuadNode.h"

using namespace slt;

QuadNode::QuadNode(sf::Vector2f pos, sf::FloatRect range, QuadNode * parent) : m_parent(parent), m_pos(pos), m_range(range)
{
    for (int i = 0; i < 4; i++) {
        this->m_Children[i] = nullptr;
    }
}

QuadNode::~QuadNode()
{
    this->m_parent = nullptr;
    for (int i = 0; i < 4; i++) {
        delete this->m_Children[i];
        this->m_Children[i] = nullptr;
    }
    this->m_node.clear();
}
