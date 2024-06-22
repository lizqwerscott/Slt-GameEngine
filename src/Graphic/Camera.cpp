#include "slt/Graphic/Camera.h"
#include "slt/Scene/SNode.h"
#include "slt/Graphic/Graphic.h"

using namespace slt;

Camera::Camera(std::string _name, sf::FloatRect rect)
    : Object(_name), view(rect)
{
    this->SetDraw(false);
}

Camera::Camera(std::string _name, sf::Vector2f center, sf::Vector2f size)
    : Object(_name), view(center, size)
{
    this->SetDraw(false);
}

Camera::~Camera() {}

void Camera::move(sf::Vector2f offset)
{
    this->view.move(offset);
}

void Camera::move(float offsetX, float offsetY)
{
    this->view.move(offsetX, offsetY);
}
void Camera::rotate(float angle)
{
    this->view.setRotation(angle);
}
void Camera::setPosition(sf::Vector2f pos)
{
    this->view.setCenter(pos);
}

void Camera::setPosition(float x, float y)
{
    this->view.setCenter(x, y);
}

void Camera::setSize(sf::Vector2f size)
{
    this->view.setSize(size);
}

void Camera::setSize(float width, float height)
{
    this->view.setSize(width, height);
}

void Camera::zoom(float factor)
{
    this->view.zoom(factor);
}

void Camera::setTrack(SNode *node, bool isAutoSize/* = false*/)
{
    this->isTrack = true;
    this->isAutoSize = isAutoSize;
    this->trackNode = node;
}

SNode *Camera::stopTrack()
{
    this->isTrack = false;
    this->isAutoSize = false;
    auto trackNode = this->trackNode;
    this->trackNode = nullptr;
    return trackNode;
}

void Camera::UpdateSelf(sf::Time &dt)
{
    if (this->isTrack) {
        auto pos = this->trackNode->GetPosition();
        auto pixel_pos = Math::WorldCoordSToDrawCoordS(pos);
        this->view.setCenter(sf::Vector2f(pixel_pos.x, pixel_pos.y));
        if (!this->isAutoSize) {
            auto windowSize = Graphic::getWindowSize();
            this->view.setSize(sf::Vector2f(windowSize.x, windowSize.y));
        }
    }
}

void Camera::DrawSelf()
{
    Graphic::SetView(this->view);
}
