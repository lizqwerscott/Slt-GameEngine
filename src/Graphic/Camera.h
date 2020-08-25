#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

namespace slt
{

class Camera
{
public:
  void move(sf::Vector2f offset);
  void move(float offsetX, float offsetY);
  void rotate(float angle);
  void setPosition(sf::Vector2f pos);
  void setPosition(float x, float y);
  void zoom(float factor);
public:
  inline sf::View & getView() {return view;}
  inline std::string & getName() {return name;}
public:
	Camera(std::string _name, sf::FloatRect rect);
	Camera(std::string _name, sf::Vector2f center, sf::Vector2f size);
	~Camera();
private:
  sf::View view;
  std::string name;
};
}

#endif
