/*
*Edit by lscott at 2018 8 12 10:55
*Manager endgine and game run
 */

#include "Application.h"
#include "AllSub.h"

using namespace slt;

Application::Application()
{
	this->engine = new Engine();
}

Application::~Application()
{
	this->engine = nullptr;
}

int Application::run()
{
	int EXIT = 0;
	init();
	Math::init(Graphic::getWindowSize());
	sf::Clock clockL;
	int runEngine = 0;
	while (engine->isClose() && runEngine == 0)
    {
        sf::Time elapsed = clockL.restart();
        runEngine = engine->Run(elapsed);
        sf::Event event;
		while (Graphic::PollWindowEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				Graphic::Close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				Graphic::findKeyCallBack(event.key.code);
			}
			else
			{

			}
		}
    }
    printf("EngineEnd\n");
    EXIT = runEngine;
    end();
    engine->release();
    engine = nullptr;
	return EXIT;
}
