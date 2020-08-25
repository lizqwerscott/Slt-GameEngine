#include "Camera.h"
#include "Graphic.h"

using namespace slt;

Camera::Camera(std::string _name, sf::FloatRect rect)
    : name(_name), view(rect) {}

Camera::Camera(std::string _name, sf::Vector2f center, sf::Vector2f size)
    : name(_name), view(center, size) {}

Camera::~Camera() {}

void Camera::move(sf::Vector2f offset) {
  this->view.move(offset);
  Graphic::SetView(this->view);
}

void Camera::move(float offsetX, float offsetY) {
  this->view.move(offsetX, offsetY);
  Graphic::SetView(this->view);
}
void Camera::rotate(float angle) {
  this->view.rotate(angle);
  Graphic::SetView(this->view);
}
void Camera::setPosition(sf::Vector2f pos) {
  this->view.setCenter(pos);
  Graphic::SetView(this->view);
}

void Camera::setPosition(float x, float y) {
  this->view.setCenter(x, y);
  Graphic::SetView(this->view);
}

void Camera::zoom(float factor) {
  this->view.zoom(factor);
  Graphic::SetView(this->view);
}
