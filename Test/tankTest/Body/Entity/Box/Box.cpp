#include "Box.h"
#include "../../Item/Item.h"

Box::Box(std::string name, GameObject *parent, PhysicalWorld * world, double volume, double quality,
         b2Vec2 nodePos, double hp) :
    Entity(name, parent, nodePos, hp),
    BoxBase(volume, quality)
{
    this->SetPosition(nodePos);
    b2Vec2 localWorldPos(0, 0);
    b2BodyDef bodyDef;
    bodyDef.type = b2BodyType::b2_kinematicBody;
    bodyDef.position =
        Math::WorldCoordSToPhysicalCoordS(nodePos + localWorldPos);
    bodyDef.angle = 0;
    bodyDef.bullet = true;
    auto physicalBody = CreatePhysicalBody(std::string("BaffleBody"), localWorldPos, bodyDef, world);
    b2PolygonShape polygonShape;
    // polygonShape.SetAsBox(3, 1, Math::WorldCoordSToPhysicalCoordS(nodePos
    // + localWorldPos), 0);
    polygonShape.SetAsBox(2, 2, b2Vec2(0, 0), 0);
    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.5;
    fixtureDef.friction = 0.2;
    fixtureDef.restitution = 1;
    fixtureDef.shape = &polygonShape;
    auto fixture = physicalBody->CreateFixture(std::string("BoxFixture"), fixtureDef);
    physicalBody->GetBody()->GetUserData().data.push_back(static_cast<void*>(this));
    fixture->m_fixture->GetUserData().data.push_back(static_cast<void*>(this));
    this->m_isDrawUi = false;
}

Box::~Box() {}

void Box::onFace(Person *person)
{
    printf("[Box]report box\n");
    this->m_isDrawUi = true;
}

void Box::DrawUiSelf()
{
    if (this->m_isDrawUi) {
        ImGui::Begin("Container");
        if (ImGui::BeginTable("Container", 3, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings)) {
            int i = 0;
            for (auto iter : m_container) {
                auto item = std::string(iter.first);
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Selectable(item.c_str(), &m_selectItem[i], ImGuiSelectableFlags_SpanAllColumns);
                auto number = std::to_string(iter.second.size());
                ImGui::TableNextColumn();
                ImGui::Text(number.c_str());
                i++;
            }
            ImGui::EndTable();
        }
        ImGui::End();
    }
}
