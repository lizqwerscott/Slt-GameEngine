#include "Thruster.h"
#include "../../Net/NetControlDevice/NetControlDevice.h"
#include <nlohmann/json.hpp>

Thruster::Thruster(std::string name, GameObject * parent, b2Vec2 size, float maxThrust, b2Vec2 nodePos, double hp) :
    Entity(name, "Thruster", parent, nodePos, hp),
    m_thrust(0),
    m_maxThrust(maxThrust),
    m_pushDirection(b2Vec2(0, 1))
{
    this->m_netControl = new NetControlDevice();
    this->m_isDrawUi = false;

    auto device = static_cast<NetControlDevice *>(this->m_netControl);
    device->subscribeRecive(DeviceSignalType::String, [this](DeviceSignal &signal) -> void {
	    auto dataA = static_cast<DeviceSignalDataString *>(signal.data);
	    Log::printLog("Recive String: %s\n", dataA->data.c_str());
	    auto dataRes = static_cast<DeviceSignalDataString *>(signal.res);
	    dataRes->data = "Yes";
	});

    device->subscribeRecive(DeviceSignalType::Json, [](DeviceSignal &data) -> void {
	    // auto dataA = static_cast<DeviceSignalDataJson &>(data);
	    // nlohmann::json jsonData = nlohmann::json::parse(dataA.data);
	    // jsonData[""]
	});


    sf::Texture * thruster = ResourceManager::GetTexture("thruster");
    thruster->setSmooth(true);

    m_mainShape = CreateRectangleShape(size, thruster);
}

void Thruster::setThrust(float thrust)
{
    if (m_thrust <= m_maxThrust && m_thrust >= 0) {
        m_thrust = thrust;
    }
}

void Thruster::increaseThrust(float step)
{
    if (m_thrust + step <= m_maxThrust) {
        m_thrust += step;
    }
}

void Thruster::decreaseThrust(float step)
{
    if (m_thrust - step >= 0) {
        m_thrust -= step;
    }
}

void Thruster::push()
{
    m_isPush = !m_isPush;
}

void Thruster::UpdateSelf(sf::Time &dt)
{
    this->m_netControl->UpdateSelf(dt);
    float angle = m_physicalBody->GetBody()->GetAngle();
    b2Mat22 mat(cos(angle), sin(angle), -sin(angle), cos(angle));
    m_pushDirection = mat.Solve(b2Vec2(0, 1));
    if (m_isPush) {
        m_physicalBody->GetBody()->ApplyForceToCenter(b2Vec2(m_pushDirection.x * m_thrust, m_pushDirection.y * m_thrust), true);
        Log::printLog("push:%f, %f\n", m_pushDirection.x, m_pushDirection.y);
    }
}
