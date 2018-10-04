#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "MemoryManager/Ref.h"

#include "Event/EventSender.h"
#include "Event/EventReciver.h"

namespace slt
{
class Object : public Ref, public EventSender, public EventReciver
{
public:
	Object(std::string name);
	virtual ~Object();
public:
	virtual void init() = 0;
	virtual void Update(sf::Time &dt, b2Vec2 parentsWorldPos) {};
	virtual void UpdateSelf(sf::Time &dt) {};
	virtual void Draw() {};
	virtual void DrawSelf() {};
public:
	std::string GetName();
	bool GetActive();
	bool GetDraw();
public:
	void SetActive(bool isActive);
	void SetDraw(bool isDraw);
protected:
	bool m_isActive = true;
	bool m_isDraw = true;
private:
	std::string m_name;
};
}

#endif
