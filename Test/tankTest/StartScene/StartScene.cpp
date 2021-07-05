#include "StartScene.h"
#include <cstdlib>
#include <ctime>
//#define random(a, b) (rand() % (b - a + 1) + a)
#include "../MainScene/MainScene.h"

StartScene::StartScene() : Scene(std::string("StartScene")) {}

StartScene::~StartScene() {}

StartScene * StartScene::create() {
    StartScene * scene = new StartScene();
    scene->init();
    return scene;
}

void StartScene::init() {
    ResourceManager::LoadFontFromFile(std::string("/home/lizqwer/project/Slt-GameEngine/resource/font/yudit.ttf"), std::string("yudit"));
    Graphic::insertKeyCallBack(sf::Keyboard::Key::S, []() -> void {
        auto MainScene = MainScene::create();
        SceneManager::pop_();
        SceneManager::SetRunScene(MainScene);
            });
}

void StartScene::UpdateSelf(sf::Time &dt) {
    auto text = new sf::Text();
    text->setFont(*ResourceManager::GetFont("yudit"));
    text->setString("Press s start Game");
    text->setCharacterSize(24);
    text->setFillColor(sf::Color::Green);
    text->setPosition(0.f, 0.f);
    text->setStyle(sf::Text::Bold | sf::Text::Underlined);
    Graphic::insert(text);
}

