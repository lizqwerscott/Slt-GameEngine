#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>
#include "../Object.h"

namespace slt
{
class SNode;

class Camera : public Object
{
public:
    void move(sf::Vector2f offset);
    void move(float offsetX, float offsetY);
    void rotate(float angle);
    void setPosition(sf::Vector2f pos);
    void setPosition(float x, float y);
    void setSize(sf::Vector2f size);
    void setSize(float width, float height);
    void zoom(float factor);
public:
    void setTrack(SNode * node, bool isAutoSize = false);
    SNode * stopTrack();
public:
    virtual void init() override {}
    virtual void Update(sf::Time &dt, b2Vec2 parentsWorldPos) override {}
    virtual void UpdateSelf(sf::Time &dt) override;
    virtual void Draw() override {}
    virtual void DrawSelf() override;
public:
    inline sf::View & getView()
    {
        return view;
    }
public:
    Camera(std::string _name, sf::FloatRect rect);
    Camera(std::string _name, sf::Vector2f center, sf::Vector2f size);
    ~Camera();
private:
    bool isTrack = false;
    bool isAutoSize = false;
    SNode * trackNode = nullptr;
    sf::View view;
};
}

#endif
