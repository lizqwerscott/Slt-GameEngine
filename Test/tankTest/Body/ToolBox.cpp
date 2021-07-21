#include "ToolBox.h"
#include "Item/Item.h"
#include "ItemTManager.h"

ToolBox::ToolBox(double volume, double quality) : 
    ContainerBase(volume, quality)
{
}

ToolBox::~ToolBox()
{
    if (m_container != nullptr) {
        delete m_container;
        m_container = nullptr;
    }
}

void ToolBox::DrawBoxUi(std::string name, int column)
{
    if (ImGui::BeginTable(name.c_str(), column, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings)) {
        ImGui::TableSetupColumn(name.c_str());
        ImGui::TableHeadersRow();
        if (m_container != nullptr) {
                auto item = m_container->getName();
                ImGui::TableNextColumn();
                ImGui::Button(std::string(item).c_str());
                if (ImGui::IsItemActive()) {
                    ItemTManager::drag(this, item);
                } else {
                    if (ItemTManager::isDrag()) {
                        ItemTManager::disDrag();
                    }
                }
        }
        ImGui::EndTable();
    }
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem)) {
        if (ItemTManager::isDrag()) {
            ItemTManager::hoveredBox(this);
        }
    } else {
        if (ItemTManager::isDrag()) {
            ItemTManager::disHoveredBox(this);
        }
    }
}

bool ToolBox::addItem(Item *item)
{
    if (m_container == nullptr) {
        m_container = item;
        return true;
    } else {
        return false;
    }
}

Item * ToolBox::getItem()
{
    return m_container;
}

bool ToolBox::transferItem(ContainerBase *target, std::string name, int number)
{
    if (m_container != nullptr) {
        if (target->addItem(m_container)) {
            m_container = nullptr;
            return true;
        }
    }
    return false;
}



