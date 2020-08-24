/*
*Test The Applicaton
 */

#include "MyApplication.h"
#include "../../src/AllSub.h"
#include "BreakoutScene/MyBreakoutScene.h"

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
	auto MainScene = MyBreakoutScene::create();
  SceneManager::SetRunScene(MainScene);
}

void MyApplication::end()
{

}

