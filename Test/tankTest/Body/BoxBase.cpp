#include "BoxBase.h"
#include "Item/Item.h"
#include "ItemTManager.h"

BoxBase::BoxBase(double volume, double quality) :
    ContainerBase(volume, quality)
{
}

BoxBase::~BoxBase()
{
    for (auto items : m_container) {
        for (auto item : items.second) {
            delete item;
            item = nullptr;
        }
        items.second.clear();
    }
    m_container.clear();
}

void BoxBase::DrawBoxUi(std::string name, int column)
{
    if (ImGui::BeginTable(name.c_str(), column, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings)) {
        ImGui::TableSetupColumn(name.c_str());
        ImGui::TableHeadersRow();
        int i = 0;
        for (auto iter : m_container) {
            if (!iter.second.empty()) {
                auto item = std::string(iter.first);
                auto number = std::to_string(iter.second.size());
                ImGui::TableNextColumn();
                ImGui::Button(std::string(item + ": " + number).c_str());
                if (ImGui::IsItemActive()) {
                    ItemTManager::drag(this, item);
                } else {
                    if (ItemTManager::isDrag()) {
                        ItemTManager::disDrag();
                    }
                }
                i++;
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

bool BoxBase::addItem(Item * item)
{
    bool qualityP = item->getQuality() <= this->m_maxQuality - this->m_nowQuality;
    bool volumeP = item->getVolume() <= this->m_maxVolume - this->m_nowVolume;
    bool addP = qualityP && volumeP;
    if (addP) {
        //this->m_container.push_back(item);
        this->m_container[item->getName()].push_back(item);
        this->m_nowQuality -= item->getQuality();
        this->m_nowVolume -= item->getVolume();
    }
    return addP;
}

std::vector<Item *>
BoxBase::getItem(std::string name, int number)
{
    std::vector<Item *> m_result;
    auto iter = m_container.find(name);
    if (iter != m_container.end()) {
        if (static_cast<int>(iter->second.size()) >= number) {
            for (int i = 0; i < number; i++) {
                m_result.push_back(iter->second[i]);
                iter->second.erase(iter->second.begin() + i);
            }
        }
    }
    return m_result;
}

Item *
BoxBase::getItem() {
    for (auto iter : m_container) {
        return iter.second[0];
    }
    return nullptr;
}

bool BoxBase::transferItem(ContainerBase * target, std::string name, int number)
{
    auto iter = m_container.find(name);
    if (iter != m_container.end()) {
        if (static_cast<int>(iter->second.size()) >= number) {
            bool add;
            for (int i = 0; i < number; i++) {
                add = target->addItem(iter->second[i]);
                if (add) {
                    iter->second.erase(iter->second.begin() + i);
                } else {
                    return false;
                }
            }
            return true;
        } else {
            printf("number bigger than have\n");
            return false;
        }
    }
    return false;
}

void BoxBase::releaseEmptyItems()
{
    for (auto iter = m_container.begin(); iter != m_container.end(); iter++) {
        if (iter->second.empty()) {
            printf("release %s\n", iter->first.c_str());
            m_container.erase(iter);
        }
    }
}

