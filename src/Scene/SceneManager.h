/*
* @Author: lscott
* @Date:   2018-06-18 09:27:06
* @Last Modified by:   lscott
* @Last Modified time: 2018-06-18 09:27:06
*/

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <map>
#include <string>
#include <list>
#include <memory>
#include "../Math/Tree.h"

namespace slt
{
class Scene;

class SceneManager
{
public:
    static void init();
    static void Destory();
public:
	static Scene * GetRunScene();
	static void SetRunScene(Scene * scene);
	static void push_(Scene * scene);
	static void pop_();
private:
	static Scene * GetSceneBack();
private:
    SceneManager();
    ~SceneManager();
private:
	std::list<Scene *> m_Scenes;
};
}
#endif
