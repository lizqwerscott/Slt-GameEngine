#include "Computer.h"
#include "../Thruster/Thruster.h"
#include "../Biological/Person.h"
#include "../Seat/Seat.h"

Computer::Computer(std::string name, GameObject * parent, b2Vec2 nodePos, double hp) :
    Entity(name, "Computer", parent, nodePos, hp)
{
    this->m_isDrawUi = false;
    m_isControl = true;
    m_isConnect = true;

    sf::Texture * computer = ResourceManager::GetTexture("computer");
    computer->setSmooth(true);

    m_mainShape = CreateRectangleShape(b2Vec2(1, 1), computer);

    cl_object (*_push)(cl_object computerId, cl_object id, cl_object force) = [](cl_object computerId, cl_object id, cl_object force) -> cl_object {
        int _cId = ecl_to_int32_t(computerId);
        int _id = ecl_to_int32_t(id);
        int _force = ecl_to_int32_t(force);
        Log::setLevel(LOG_LEVEL_INFO);
        Log::printLog("%d, %d, %d\n", _cId, _id, _force);
        Computer::push(_cId, _id, _force);
        return ECL_NIL;
    };
    DEFUN("pushShip", _push, 3);

    float force = 90;
    Graphic::insertKeyCallBack(sf::Keyboard::Key::W, GetId(), [force, this]() -> void {
        if (m_seat != nullptr && m_seat->m_person != nullptr)
        {
            this->move(0, force);
        }
    });
    Graphic::insertKeyCallBack(sf::Keyboard::Key::S, GetId(), [force, this]() -> void {
        if (m_seat != nullptr && m_seat->m_person != nullptr)
        {
            this->move(1, force);
        }
    });
    Graphic::insertKeyCallBack(sf::Keyboard::Key::A, GetId(), [force, this]() -> void {
        if (m_seat != nullptr && m_seat->m_person != nullptr)
        {
            this->move(2, force);
        }
    });
    Graphic::insertKeyCallBack(sf::Keyboard::Key::D, GetId(), [force, this]() -> void {
        if (m_seat != nullptr && m_seat->m_person != nullptr)
        {
            this->move(3, force);
        }
    });
}

Computer::~Computer()
{
}

void Computer::onFace(Person *person)
{
    Log::setLevel(LOG_LEVEL_INFO);
    Log::printLog("[Computer]report computer\n");
    this->m_isDrawUi = !this->m_isDrawUi;
}

void Computer::addControl(Entity * entity)
{
    auto iter = find_if(m_thrusters.begin(), m_thrusters.end(), [entity](Thruster * thruster) -> bool {
        return thruster->GetId() == entity->GetId();
    });
    if (iter == m_thrusters.end()) {
        if (entity->m_typeName == std::string("Thruster")) {
            Thruster * thruster = static_cast<Thruster *>(entity);
            Log::setLevel(LOG_LEVEL_INFO);
            Log::printLog("add thruster\n");
            m_thrusters.push_back(thruster);
        }
    } else {
        if (entity->m_typeName == std::string("Seat")) {
            if (m_seat == nullptr) {
                m_seat = static_cast<Seat *>(entity);
            }
        }
        Log::setLevel(LOG_LEVEL_ERROR);
        Log::printLog("Added, %u\n", entity->GetId());
    }
}

void Computer::DrawUiSelf()
{
    if (m_isDrawUi) {
        ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_FirstUseEver);
        ImGui::Begin("Computer");

        float force = 100;
        if (ImGui::Button("Up")) {
            move(0, force);
        }
        ImGui::SameLine();
        if (ImGui::Button("Down")) {
            move(1, force);
        }
        ImGui::SameLine();
        if (ImGui::Button("Left")) {
            move(2, force);
        }
        ImGui::SameLine();
        if (ImGui::Button("Right")) {
            move(3, force);
        }
        ImGui::SameLine();
        if (ImGui::Button("Push")) {
            for (auto thruster : m_thrusters) {
                thruster->increaseThrust(10);
                thruster->push();
                Log::setLevel(LOG_LEVEL_INFO);
                Log::printLog("Push\n");
            }
        }
        if (ImGui::Button("GetInfo")) {
            Log::setLevel(LOG_LEVEL_INFO);
            Log::printLog("this angle:%u, %f\n", GetId(), GetAngle());
            for (auto thruster : m_thrusters) {
                Log::printLog("thruster:%u, %f, Direction:%f, %f\n", thruster->GetId(), thruster->GetAngle(), thruster->m_pushDirection.x, thruster->m_pushDirection.y);
            }
        }
        if (ImGui::Button("LoadScripts")) {
            Script::lisp("(load \"/home/lizqwer/project/Slt-GameEngine/Test/tankTest/Scripts/test.lisp\")");
        }
        ImGui::End();
    }
}

void Computer::move(int direction, float force)
{
    auto wucha = [](float angle1, float angle2, float wuc = 0.1) -> bool {
        return abs(angle1 - angle2) <= 0.1;
    };
    std::vector<Thruster *> _direction;

    switch (direction) {
    case 0: {
        for (auto thruster : m_thrusters) {
            float angle = thruster->GetAngle();
            if (wucha(angle, GetAngle())) {
                _direction.push_back(thruster);
            }
        }
        for (auto thruster : _direction) {
            thruster->setThrust(force);
            thruster->push();
        }
    }
    break;
    case 1: {
        for (auto thruster : m_thrusters) {
            float angle = thruster->GetAngle();
            if (wucha(angle, GetAngle() + PI)) {
                _direction.push_back(thruster);
            }
        }
        for (auto thruster : _direction) {
            thruster->setThrust(force);
            thruster->push();
        }
    }
    break;
    case 2: {
        for (auto thruster : m_thrusters) {
            float angle = thruster->GetAngle();
            if (wucha(angle, GetAngle() + PI + PI / 2)) {
                _direction.push_back(thruster);
            }
        }
        for (auto thruster : _direction) {
            thruster->setThrust(force);
            thruster->push();
        }
    }
    break;
    case 3: {
        for (auto thruster : m_thrusters) {
            float angle = thruster->GetAngle();
            if (wucha(angle, GetAngle() + PI / 2)) {
                _direction.push_back(thruster);
            }
        }
        for (auto thruster : _direction) {
            thruster->setThrust(force);
            thruster->push();
        }
    }
    break;
    default:
        break;
    }


}

void Computer::UpdateSelf(sf::Time &dt)
{
}

Computer * Computer::findSelf(int id)
{
    auto entity = static_cast<Entity *>(SceneManager::GetRunScene()->GetRootNode()->GetChild(id));
    if (entity != nullptr && entity->m_typeName == std::string("Computer")) {
        return static_cast<Computer *>(entity);
    } else {
        return nullptr;
    }
}

cl_object Computer::getThrusters()
{
}

void Computer::push(int computerId, int id, int force)
{
    Computer * computer = Computer::findSelf(computerId);
    if (computer != nullptr) {
        auto thrusters = computer->m_thrusters;
        auto iter = find_if(thrusters.begin(), thrusters.end(), [id](Thruster * item) -> bool {
            return item->GetId() == (unsigned int)id;
        });

        if (iter != thrusters.end()) {
            Thruster * thruster = *iter;
            thruster->setThrust(force);
            thruster->push();
        }
    }
}

//void Computer::move(int direction, float force)
//{
//}

void Computer::rotate(float angle)
{
}
