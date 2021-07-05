/*
*Test The Applicaton
 */

#include "MyApplication.h"
#include "../../src/AllSub.h"
#include "MainScene/MainScene.h"
#include "StartScene/StartScene.h"

MyApplication::MyApplication()
{

}

MyApplication::~MyApplication()
{

}

void MyApplication::init()
{
	Graphic::init();
	Math::init(Graphic::getWindowSize());
    auto StartScene = StartScene::create();
	//auto MainScene = MainScene::create();

    SceneManager::SetRunScene(StartScene);
}

void MyApplication::end()
{

}

