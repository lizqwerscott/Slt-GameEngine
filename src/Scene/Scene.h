 /*
* @Author: lscott
* @Date:   2018-06-18 09:29:56
* @Last Modified by:   lscott
* @Last Modified time: 2018-06-18 09:29:56
*/

#ifndef SCENE_H
#define SCENE_H

#include <functional>
#include <Box2D/Box2D.h>
#include <memory>
#include "../Math/Tree.h"
#include "../Object.h"

namespace slt
{
class View;
class SNode;
class PhysicalWorld;
class Camera;

class Scene : public Tree<SNode>, public Object
{
public:
    Scene(std::string name, sf::FloatRect range = sf::FloatRect(0, 0, 800.0, 800.0), bool isActive = true);
    virtual ~Scene();
public:
	virtual void init() override {}
	void SetRange(sf::FloatRect range);
	sf::FloatRect GetRange();
public:
    virtual void Update(sf::Time &dt, b2Vec2 parentsWorldPos = b2Vec2(0, 0)) override;
    virtual void UpdateSelf(sf::Time &dt) override {}
    virtual void Draw() override;
    virtual void DrawSelf() override {}
public:
	std::shared_ptr<PhysicalWorld> CreatePhysicalWorld(std::string name, bool isOpenDebugDraw = false, b2Vec2 gravity = b2Vec2(0, 0), int32 vI = 8, int32 pI = 3);
	void DeletePhysicalWorld();
	std::shared_ptr<PhysicalWorld> GetPhysicalWorld();
public:
	void pushUpdateCallBack(std::function<void(Scene *)> updateCallBack);
	void pushDrawCallBack(std::function<void(Scene *)> drawCallBack);
	void popUpdateCallBack();
	void popDrawCallBack();
public:
  inline std::shared_ptr<Camera> getCamera(std::string name = "Main") {return this->m_cameras[name];}
private:
	std::vector<std::function<void(Scene *)>> m_UpdateCallBacks;
	std::vector<std::function<void(Scene *)>> m_DrawCallBacks;
private:
  std::map<std::string, std::shared_ptr<Camera>> m_cameras; 
	sf::FloatRect m_loadRange;
	std::shared_ptr<PhysicalWorld> m_physicalWorld;
};
}
#endif
