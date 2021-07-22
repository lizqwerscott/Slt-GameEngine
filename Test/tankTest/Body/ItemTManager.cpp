#include "ItemTManager.h"
#include "BoxBase.h"
#include "../../../src/AllSub.h"

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

void ItemTManager::drag(ContainerBase *box, std::string name)
{
    //printf("drag: %s\n", name.c_str());
    instance->m_isDrag = true;
    instance->m_box = box;
    instance->m_dragName = name;
}

void ItemTManager::disDrag()
{
    if (instance->m_lastHoveredBox != nullptr && !ImGui::IsMouseDragging(0)) {
    }
    if (!ImGui::IsMouseDragging(0)) {
        if (instance->m_lastHoveredBox != nullptr) {
            instance->m_box->transferItem(instance->m_lastHoveredBox, instance->m_dragName, 1);
            instance->m_isDrag = false;
            instance->m_box = nullptr;
            instance->m_dragName = "";
            instance->m_lastHoveredBox = nullptr;
        }
        instance->m_isDrag = false;
    } else {
        ImVec2 mousePos = ImGui::GetMousePos();
        ImGui::GetForegroundDrawList()->AddText(ImVec2(mousePos.x + 10, mousePos.y + 10), ImGui::GetColorU32(ImGuiCol_Button), instance->m_dragName.c_str());
    }
}

bool ItemTManager::isDrag()
{
    return instance->m_isDrag;
}

void ItemTManager::hoveredBox(ContainerBase *box)
{
    if (box != instance->m_lastHoveredBox && box != instance->m_box) {
        instance->m_lastHoveredBox = box;
        printf("hoveredBox\n");
    }
}

void ItemTManager::disHoveredBox(ContainerBase *box)
{
    if (box == instance->m_lastHoveredBox) {
        instance->m_lastHoveredBox = nullptr;
    }
}
