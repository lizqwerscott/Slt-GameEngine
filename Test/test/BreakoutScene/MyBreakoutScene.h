#ifndef MYBREAKOUTSCENE_H
#define MYBREAKOUTSCENE_H

#include "../../../src/AllSub.h"

using namespace slt;

/**
 * @brief      Class for my slt scene.
 */
class MyBreakoutScene : public Scene
{
public:
	MyBreakoutScene();
	~MyBreakoutScene();
public:
	static MyBreakoutScene * create();
	virtual void init() override;
	virtual void UpdateSelf(sf::Time &dt) override;
	virtual void OnEvent(EventSender * sender, EventKey key, EventData &eventData);
private:
	b2Vec2 speed;
};

#endif
