/*
*Test The Applicaton
 */

#include "MyApplication.h"
#include "../../src/AllSub.h"
#include "MainScene/MainScene.h"

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
	auto MainScene = MainScene::create();

    SceneManager::SetRunScene(MainScene);
}

void MyApplication::end()
{

}

