#ifndef ITEMTMANAGER_H
#define ITEMTMANAGER_H

#include "../../../src/AllSub.h"

using namespace slt;

class BoxBase;

class ItemTManager
{
public:
public:
    static void Create();
    static void Destory();
public:
    static void drag(BoxBase * box, std::string name);
    static void disDrag();
    static bool isDrag();
    static void hoveredBox(BoxBase * box);
    static void disHoveredBox(BoxBase * box);
private:
    // when mouse drag item, they put it in this;
    BoxBase * m_box = nullptr;
    std::string m_dragName;
    bool m_isDrag = false;
    //when mouse hovered box, they put it in this;
    BoxBase * m_lastHoveredBox = nullptr;
private:
    ItemTManager() {}
    virtual ~ItemTManager() {}
};

#endif /* ITEMTMANAGER_H */
