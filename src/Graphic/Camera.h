#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

namespace slt
{

class Camera : public sf::View
{
public:
	Camera(sf::FloatRect rect);
	~Camera();
};
}

#endif
