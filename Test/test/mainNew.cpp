/*
* @Author: lscott
* @Date:   2018-06-18 17:02:04
* @Last Modified by:   lscott
* @Last Modified time: 2018-06-21 13:33:15
*/

#include <iostream>
#include "Root.h"
#include "Engine/Engine.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include <memory>
#include "ResourceManager/ResourceManager.h"

int main(int argc, char const *argv[])
{
    //Time
	sf::Clock clockL;
    Breakout::Engine * engine = new Breakout::Engine(800, 800, std::string("The Test"));

    sf::View view(sf::FloatRect(0, 0, 800, 800));
    engine->setView(view);
    
    auto MainScene = new Breakout::Scene(std::string("MainScene"), sf::FloatRect(0, 0, 800, 800));
    Breakout::SceneManager::SetRunScene(MainScene);
    Breakout::SNode * node = MainScene->GetRootNode()->CreateChild(std::string("Node"));
    auto sprite = node->CreateSprite(std::string("ballSprite"));
    sprite->setTexture(*ResourceManager::LoadTextureFromFile("/home/lscott/Documents/Projrect/Breakout_2_2/resource/image/Ball.png", "ball"));
    sprite->setColor(sf::Color(0, 255, 0));

    int runEngine = 0;
    while (engine->isClose() && runEngine == 0)
    {
        sf::Time elapsed = clockL.restart();
        runEngine = engine->Run(elapsed);
    }

    engine->release();
    return runEngine;
}
