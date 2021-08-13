#include "Seat.h"
#include "../Biological/Person.h"

Seat::Seat(std::string name, GameObject * parent, b2Vec2 nodePos, double hp) :
    Entity(name, "Seat", parent, nodePos, hp)
{
    this->m_isDrawUi = false;

    sf::Texture * seat = ResourceManager::GetTexture("seat");
    seat->setSmooth(true);

    m_mainShape = CreateRectangleShape(b2Vec2(1, 3), seat);
    Graphic::insertKeyCallBack(sf::Keyboard::Key::T, GetId(), [this]() -> void {
        m_person->SetPosition(m_pos + GetPosition());
        m_person->m_physicalBody->GetFixture()->m_fixture->SetSensor(false);
        m_person->SetDraw(true);
        m_person = nullptr;
        m_pos = b2Vec2(0, 0);
    });
}

Seat::~Seat()
{
}

void Seat::onFace(Person *person)
{
    person->m_physicalBody->GetFixture()->m_fixture->SetSensor(true);
    m_pos = person->GetPosition() - GetPosition();
    person->SetPosition(GetPosition());
    m_person = person;
    m_person->SetDraw(false);
}

void Seat::UpdateSelf(sf::Time &dt)
{
    if (m_person != nullptr) {
        m_person->SetPosition(GetPosition());
    }
}

void Seat::DrawSelf()
{
    if (m_person != nullptr) {
    }
}

