#ifndef NODE_H
#define NODE_H

//edit by lscott at 2018 7 20 18:34

#include <list>
#include <string>
#include <cstdio>
#include <algorithm>

namespace slt
{
template<typename T>
class Node
{
public:
    Node(T * parent = nullptr) : m_parent(parent) {}
    virtual ~Node()
    {
        this->m_parent = nullptr;
        for (auto nextNode : this->m_next) {
            delete nextNode;
        }
        this->m_next.clear();
    }
public:
    T * GetParent()
    {
        return this->m_parent;
    }
protected:
    std::list<T *> m_next;
private:
    T * m_parent = nullptr;
};
}
#endif
