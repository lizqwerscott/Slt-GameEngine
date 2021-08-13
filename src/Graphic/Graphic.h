#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace slt {
class PhysicalWorld;
class View;
class Camera;

class Graphic : public b2Draw {
public:
  static void init(std::string tile = "The Window", int width = 1920,
                   int height = 1080);
  static Graphic *getInstance();
  static void Destory();

public:
  static void insert(sf::Sprite *sprite);
  static void insert(sf::Shape *shape);
  static void insert(sf::Text *text);
  static void insertLine(std::vector<sf::Vertex> line);
  static void insertLine(sf::Vector2f start, sf::Vector2f end);
  static void insertPolygon(std::vector<sf::Vertex> polygon);

  static void SetView(sf::View &view);

  static sf::Vector2f PixelToCoords(sf::Vector2i pixelPos);

public:
  static sf::Color changeColor(b2Color color);

public:
  static void applyKeyCallBack(sf::Keyboard::Key key);
  static void insertKeyCallBack(sf::Keyboard::Key key, unsigned int sender, std::function<void(void)> keyCallBack);
  static void deleteKeyCallBack(sf::Keyboard::Key key, unsigned int sender);

  static void insertMouseWheelCallBack(std::function<void(sf::Event::MouseWheelScrollEvent)> mouseCallBack);
  static void deleteMouseWhellCallBack();
  static void mouseWhellCallBackRun(sf::Event::MouseWheelScrollEvent event);

  static void insertMouseClickCallBack(sf::Mouse::Button button, std::function<void(sf::Vector2i)> callBack);
  static void deleteMouseClickCallBack(sf::Mouse::Button button);
  static void mouseClick(sf::Mouse::Button button, sf::Vector2i pos);

  static sf::Vector2i getMousePosition();
  static b2Vec2 getMousePositionP();

  static bool isMouseInWindow();
public:
  std::shared_ptr<sf::RenderWindow> getWindow();
public:
  static void Close();

  static void Clear();
  static void Update(sf::Time &dt);
  static void Render();
  static void Display();

  static void DrawSprite(sf::Sprite *sprite);
  static void DrawShape(sf::Shape *shape);
  static void DrawText(sf::Text *text);

  static bool PollWindowEvent(sf::Event &event);

public:
  static void SetDebugDraw(PhysicalWorld *world);
  // b2DebugDraw
  void DrawPolygon(const b2Vec2 *vertices, int32 vertexCount,
                   const b2Color &color) override;

  void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount,
                        const b2Color &color) override;

  void DrawCircle(const b2Vec2 &center, float_t radius,
                  const b2Color &color) override;

  void DrawSolidCircle(const b2Vec2 &center, float_t radius, const b2Vec2 &axis,
                       const b2Color &color) override;

  void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2,
                   const b2Color &color) override;

  void DrawTransform(const b2Transform &xf) override;

  void DrawPoint(const b2Vec2 &p, float_t size, const b2Color &color);

  void DrawAABB(b2AABB *aabb, const b2Color &color);

public:
  static sf::ConvexShape *GetShape(b2PolygonShape *polygonShape, b2Vec2 pos,
                                   sf::Color color);
  static sf::CircleShape *GetShape(b2CircleShape *circleShape, sf::Color color);
  static sf::Shape *GetShape(b2Fixture *fixture, sf::Color color);
  // static sf::Shape *GetShape(b2PolygonShape * shape);
public:
  static bool isOpen();
  static sf::Vector2u getWindowSize();

private:
  Graphic(std::string tile, int width, int height);
  ~Graphic();

private:
  std::shared_ptr<sf::RenderWindow> m_window;

  std::vector<std::shared_ptr<sf::Sprite>> m_sprites;
  std::vector<std::shared_ptr<sf::Shape>> m_shapes;
  std::vector<std::shared_ptr<sf::Text>> m_texts;

  std::vector<std::vector<sf::Vertex>> m_lines;
  std::vector<std::vector<sf::Vertex>> m_polygons;

  //std::map<sf::Keyboard::Key, std::function<void(void)>> m_keyCallBacks;
  std::map<sf::Keyboard::Key, std::map<unsigned int, std::function<void(void)>>> m_keyCallBacks;
  std::function<void(sf::Event::MouseWheelScrollEvent)> m_mouseWhellCallBack;
  std::map<sf::Mouse::Button, std::function<void(sf::Vector2i)>> m_mouseClickCallBack;
};
} // namespace slt
#endif
