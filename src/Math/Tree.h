#ifndef TREE_H
#define TREE_H

// by lscott at 2018 7 20 18:30

namespace slt {
template <typename T> class Tree {
public:
  Tree() {}

public:
  T *GetRootNode() { return this->m_RootTree; }

protected:
  T *m_RootTree = nullptr;
};
} // namespace slt
#endif
