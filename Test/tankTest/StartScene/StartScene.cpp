#include "StartScene.h"
#include <cstdlib>
#include <ctime>
//#define random(a, b) (rand() % (b - a + 1) + a)
#include "../MainScene/MainScene.h"

StartScene::StartScene() : Scene(std::string("StartScene")) {}

StartScene::~StartScene() {}

StartScene * StartScene::create()
{
    StartScene * scene = new StartScene();
    scene->init();
    return scene;
}

void StartScene::init()
{
    ResourceManager::LoadFontFromFile(std::string("/home/lizqwer/project/Slt-GameEngine/resource/font/yudit.ttf"), std::string("yudit"));
}

void StartScene::DrawUi()
{
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2(Graphic::getWindowSize().x, Graphic::getWindowSize().y));
    ImGui::Begin("MainPage", nullptr, ImGuiWindowFlags_NoTitleBar);
    if (ImGui::Button("Start")) {
        auto MainScene = MainScene::create();
        SceneManager::pop_();
        SceneManager::SetRunScene(MainScene);
    }
    if (ImGui::Button("End")) {
        Graphic::Close();
    }
    ImGui::End();
}

void StartScene::UpdateSelf(sf::Time &dt)
{
}
