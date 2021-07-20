#include "ItemTManager.h"
#include "BoxBase.h"


ItemTManager * instance = nullptr;

void ItemTManager::Create()
{
    if (instance == nullptr) {
        instance = new ItemTManager();
    }
}

void ItemTManager::Destory()
{
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}

void ItemTManager::drag(BoxBase *box, std::string name)
{
    //printf("drag: %s\n", name.c_str());
    instance->m_isDrag = true;
    instance->m_box = box;
    instance->m_dragName = name;
}

void ItemTManager::disDrag()
{
    if (instance->m_lastHoveredBox != nullptr && !ImGui::IsMouseDragging(0)) {
        printf("transferItem\n");
        instance->m_box->transferItem(instance->m_dragName, instance->m_lastHoveredBox, 1);
        instance->m_isDrag = false;
        instance->m_box = nullptr;
        instance->m_dragName = "";
        instance->m_lastHoveredBox = nullptr;
    }
}

bool ItemTManager::isDrag()
{
    return instance->m_isDrag;
}

void ItemTManager::hoveredBox(BoxBase *box)
{
    if (box != instance->m_lastHoveredBox && box != instance->m_box) {
        instance->m_lastHoveredBox = box;
        printf("hoveredBox\n");
    }
}

void ItemTManager::disHoveredBox(BoxBase *box)
{
    if (box == instance->m_lastHoveredBox) {
        instance->m_lastHoveredBox = nullptr;
    }
}
