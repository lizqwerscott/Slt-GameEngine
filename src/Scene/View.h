#ifndef VIEW_H
#define VIEW_H

#include <map>
#include <string>
#include "../Graphic/Graphic.h"

namespace slt
{

class QuadTree;
class Camera;

class View
{
public:
	View(sf::FloatRect range);
	~View();
public:
	void Update(); //Update QuadTree;
	void Draw(); //Draw QuadTree in Cameras;

public:
	QuadTree * m_quadTree;
	sf::FloatRect m_viewRange;
	std::map<std::string, Camera *> m_cameras;
};
}

#endif
