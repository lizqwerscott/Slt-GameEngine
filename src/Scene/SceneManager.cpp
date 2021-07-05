/*
 * @Author: lscott
 * @Date:   2018-06-18 09:27:06
 * @Last Modified by:   lscott
 * @Last Modified time: 2018-06-19 12:40:08
 */

#include "SceneManager.h"
#include "Scene.h"
#include <iostream>

using namespace slt;

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {
  for (auto scene : this->m_Scenes) {
    scene->release();
  }
}

SceneManager *sceneManager = nullptr;

// init The SceneManager
void SceneManager::init() { sceneManager = new SceneManager(); }

// Destory The SceneManager
void SceneManager::Destory() {
  delete sceneManager;
  sceneManager = nullptr;
}

Scene *SceneManager::GetRunScene() { return SceneManager::GetSceneBack(); }

void SceneManager::SetRunScene(Scene *scene) { SceneManager::push_(scene); }

void SceneManager::push_(Scene *scene) {
  sceneManager->m_Scenes.push_back(scene);
}

void SceneManager::pop_() {
  auto scene = sceneManager->m_Scenes.back();
  delete scene;
  scene = nullptr;
  sceneManager->m_Scenes.pop_back();
}

void SceneManager::next(Scene *scene) {
    sceneManager->pop_();
    sceneManager->SetRunScene(scene);
}

Scene *SceneManager::GetSceneBack() { return sceneManager->m_Scenes.back(); }
