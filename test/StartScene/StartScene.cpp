#include "StartScene.h"
#include "slt/Script/Script.h"
#include <cstdlib>
#include <ctime>
//#define random(a, b) (rand() % (b - a + 1) + a)

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
    Script::setDrawUi();
}

void StartScene::DrawUiSelf()
{
    // auto windowSize = Graphic::getWindowSize();
    // ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    // ImGui::SetNextWindowSize(ImVec2(windowSize.x, windowSize.y));
    // ImGui::Begin("MainPage", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    // ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
    // if (ImGui::Button("Start", ImVec2(windowSize.x, windowSize.y / 2))) {
    //     // SceneManager::pop_();
    // }
    // if (ImGui::Button("End", ImVec2(windowSize.x, windowSize.y / 2))) {
    //     Graphic::Close();
    // }
    // ImGui::PopFont();
    // ImGui::End();
}

void StartScene::UpdateSelf(sf::Time &dt)
{
}
