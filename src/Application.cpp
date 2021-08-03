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
    while (engine->isClose() && runEngine == 0) {
        sf::Time elapsed = clockL.restart();
        runEngine = engine->Run(elapsed);
        sf::Event event;
        while (Graphic::PollWindowEvent(event)) {
            if (Graphic::isMouseInWindow()) {
                if (event.type == sf::Event::Closed) {
                    Graphic::Close();
                } else if (event.type == sf::Event::Resized) {
                    Math::setWindowSize(sf::Vector2u(event.size.width, event.size.height));
                } else {
                    ImGui::SFML::ProcessEvent(event);
                }
            } else {
                if (event.type == sf::Event::Closed) {
                    Graphic::Close();
                } else if (event.type == sf::Event::MouseWheelScrolled) {
                    printf("the mouse is moved, the delta is %f\n",
                           event.mouseWheelScroll.delta);
                    Graphic::mouseWhellCallBackRun(event.mouseWheelScroll);
                } else if (event.type == sf::Event::KeyPressed) {
                    Graphic::applyKeyCallBack(event.key.code);
                } else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Right) {
                        sf::Vector2i pos = Graphic::getMousePosition();
                        Graphic::mouseClick(sf::Mouse::Right, pos);
                    } else if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i pos = Graphic::getMousePosition();
                        Graphic::mouseClick(sf::Mouse::Left, pos);
                    }
                }
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
