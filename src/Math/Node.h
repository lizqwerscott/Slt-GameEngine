#ifndef NODE_H
#define NODE_H

//edit by lscott at 2018 7 20 18:34

#include <ext/hash_map>

namespace slt
{
template<typename T>
class Node
{
public:
	Node(T * parent = nullptr) : m_parent(parent) {}
	virtual ~Node() {
		this->m_parent = nullptr;
		for (auto nextNode : this->m_next)
		{
			delete nextNode.second;
		}
		this->m_next.clear();
	}
public:
	T * GetParent() {
		return this->m_parent;
	}
	T * GetChild(std::string name) {
		return this->m_next[name];
	}
protected:
	std::map<std::string, T *> m_next;
private:
	T * m_parent = nullptr;
};
}
#endif
