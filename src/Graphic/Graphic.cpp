#include "Graphic.h"
#include "../Math/Math.h"
#include "../Physical/PhysicalWorld.h"
#include "../Scene/View.h"
#include "Camera.h"
#include <iostream>

using namespace slt;

Graphic::Graphic(std::string tile, int width, int height) : m_window(nullptr) {
  this->m_window = std::shared_ptr<sf::RenderWindow>(
      new sf::RenderWindow(sf::VideoMode(width, height), tile.c_str()));
  auto camera = new Camera(std::string("Main"), sf::FloatRect(0.f, 0.f, 800.f, 700.f));
  this->m_cameras[std::string("Main")] = std::shared_ptr<Camera>(camera);
  this->m_window->setView(camera->getView());
}

Graphic::~Graphic() {}

Graphic *graphic = nullptr;

void Graphic::init(std::string tile, int width, int height) {
  graphic = new Graphic(tile, width, height);
}

void Graphic::Destory() {
  delete graphic;
  graphic = nullptr;
}

Graphic *Graphic::getInstance() { return graphic; }

void Graphic::insert(sf::Sprite *sprite) {
  graphic->m_sprites.push_back(std::shared_ptr<sf::Sprite>(sprite));
}

void Graphic::insert(sf::Shape *shape) {
  graphic->m_shapes.push_back(std::shared_ptr<sf::Shape>(shape));
}

void Graphic::insert(sf::Text *text) {
  graphic->m_texts.push_back(std::shared_ptr<sf::Text>(text));
}

void Graphic::insertLine(std::vector<sf::Vertex> line) {
  graphic->m_lines.push_back(line);
}

void Graphic::insertLine(sf::Vector2f start, sf::Vector2f end) {
  std::vector<sf::Vertex> v;
  v.push_back(start);
  v.push_back(end);
  graphic->m_lines.push_back(v);
}

void Graphic::insertPolygon(std::vector<sf::Vertex> polygon) {
  graphic->m_polygons.push_back(polygon);
}

void Graphic::SetView(sf::View &view) { graphic->m_window->setView(view); }

std::shared_ptr<Camera> Graphic::getCamera(std::string name) {
  return this->m_cameras[name];
}

sf::Vector2i Graphic::worldToPixel(sf::Vector2f pixel_pos, std::string name) {
  return this->m_window->mapCoordsToPixel(pixel_pos, this->m_cameras[name].get()->getView());
}

sf::Color Graphic::changeColor(b2Color color) {
  return sf::Color((int)(color.r * 255), (int)color.g * 255, (int)color.b * 255,
                   (int)color.a * 255);
}

void Graphic::findKeyCallBack(sf::Keyboard::Key key) {
  if (graphic->m_keyCallBacks.find(key) != graphic->m_keyCallBacks.end()) {
    graphic->m_keyCallBacks[key]();
  }
}

void Graphic::insertKeyCallBack(sf::Keyboard::Key key,
                                std::function<void(void)> keyCallBack) {
  graphic->m_keyCallBacks[key] = keyCallBack;
}

void Graphic::deleteKeyCallBack(sf::Keyboard::Key key) {
  graphic->m_keyCallBacks.erase(key);
}

void Graphic::Close() { graphic->m_window->close(); }

void Graphic::DrawSprite(sf::Sprite *sprite) {
  graphic->m_window->draw(*sprite);
}

void Graphic::DrawShape(sf::Shape *shape) { graphic->m_window->draw(*shape); }

void Graphic::DrawText(sf::Text *text) { graphic->m_window->draw(*text); }

void Graphic::Clear() { graphic->m_window->clear(); }

void Graphic::Render() {
  // Draw Start
  // Draw Sprite
  for (auto sprite : graphic->m_sprites) {
    graphic->m_window->draw(*sprite);
  }
  graphic->m_sprites.clear();
  // Draw Shape
  for (auto shape : graphic->m_shapes) {
    graphic->m_window->draw(*shape);
  }
  graphic->m_shapes.clear();
  // Draw Text
  for (auto text : graphic->m_texts) {
    graphic->m_window->draw(*text);
  }
  graphic->m_texts.clear();
  for (auto line : graphic->m_lines) {
    graphic->m_window->draw(&line[0], line.size(), sf::Lines);
  }
  graphic->m_lines.clear();
  for (auto polygon : graphic->m_polygons) {
    graphic->m_window->draw(&polygon[0], polygon.size(), sf::LinesStrip);
  }
  graphic->m_polygons.clear();
  // Draw End
}

void Graphic::Display() { graphic->m_window->display(); }

bool Graphic::PollWindowEvent(sf::Event &event) {
  return graphic->m_window->pollEvent(event);
}

void Graphic::SetDebugDraw(PhysicalWorld *world) {
  world->SetDebugDraw(graphic);
}

// b2DebugDraw
void Graphic::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount,
                          const b2Color &color) {
  std::vector<sf::Vertex> v;
  for (int i = 0; i < vertexCount; i++) {
    sf::Vertex point(Math::PhysicalCoordSToDrawCoordS(vertices[i]));
    point.color = Graphic::changeColor(color);
    v.push_back(point);
  }
  sf::Vertex pointS(Math::PhysicalCoordSToDrawCoordS(vertices[0]));
  pointS.color = Graphic::changeColor(color);
  v.push_back(pointS);
  graphic->m_polygons.push_back(v);
}

void Graphic::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount,
                               const b2Color &color) {
  sf::ConvexShape *convex = new sf::ConvexShape();
  convex->setPointCount(vertexCount);
  for (int i = 0; i < vertexCount; i++) {
    convex->setPoint(i, Math::PhysicalCoordSToDrawCoordS(vertices[i]));
  }
  convex->setFillColor(Graphic::changeColor(color));
  graphic->insert(convex);
}

void Graphic::DrawCircle(const b2Vec2 &center, float32 radius,
                         const b2Color &color) {
  std::vector<sf::Vertex> v;
  const float drawRadius = Math::MeterToPixel(radius);
  int count = drawRadius * 10;
  float unitR = 2 * PI / count;
  for (int i = 0; i < count; i++) {
    sf::Vertex point(
        Math::PhysicalCoordSToDrawCoordS(center) +
        sf::Vector2f(cos(unitR * i) * drawRadius, sin(unitR * i) * drawRadius));
    point.color = Graphic::changeColor(color);
    v.push_back(point);
  }
  sf::Vertex point(Math::PhysicalCoordSToDrawCoordS(center) +
                   sf::Vector2f(cos(0) * drawRadius, sin(0) * drawRadius));
  point.color = Graphic::changeColor(color);
  v.push_back(point);
  graphic->m_polygons.push_back(v);
}

void Graphic::DrawSolidCircle(const b2Vec2 &center, float32 radius,
                              const b2Vec2 &axis, const b2Color &color) {
  sf::CircleShape *circle = new sf::CircleShape(Math::MeterToPixel(radius));
  circle->setFillColor(Graphic::changeColor(color));
  sf::Vector2f pos = Math::PhysicalCoordSToDrawCoordS(center);
  circle->setPosition(pos - sf::Vector2f(Math::MeterToPixel(radius),
                                         Math::MeterToPixel(radius)));
  // printf("CirclePhysical:Pos:%f, %f\n", center.x, center.y);
  // printf("CircelDraw:Pos:%f, %f\n", pos.x, pos.y);
  graphic->insert(circle);
}

void Graphic::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2,
                          const b2Color &color) {}

void Graphic::DrawTransform(const b2Transform &xf) {}

void Graphic::DrawPoint(const b2Vec2 &p, float32 size, const b2Color &color) {
  sf::CircleShape *circle = new sf::CircleShape(size);
  circle->setFillColor(Graphic::changeColor(color));
  circle->setPosition(Math::PhysicalCoordSToDrawCoordS(p));
  graphic->insert(circle);
}

void Graphic::DrawAABB(b2AABB *aabb, const b2Color &color) {
  b2Vec2 vertices[4];
  b2Vec2 size = aabb->upperBound - aabb->lowerBound;
  vertices[0] = b2Vec2(aabb->upperBound);
  vertices[1] = b2Vec2(b2Vec2(aabb->upperBound.x + size.x, aabb->upperBound.y));
  vertices[2] = b2Vec2(aabb->lowerBound);
  vertices[3] = b2Vec2(b2Vec2(aabb->upperBound.x, aabb->upperBound.y + size.y));
  this->DrawPolygon(vertices, 4, color);
}

sf::ConvexShape *Graphic::GetShape(b2PolygonShape *polygonShape, b2Vec2 pos,
                                   sf::Color color) {
  sf::ConvexShape *convex = new sf::ConvexShape();
  convex->setPointCount(polygonShape->GetVertexCount());
  for (int i = 0; i < polygonShape->GetVertexCount(); i++) {
    // printf("PolygonShape:Point:%d:%f, %f\n", i, polygonShape->GetVertex(i).x,
    // polygonShape->GetVertex(i).y);
    convex->setPoint(
        i, Math::PhysicalCoordSToDrawCoordS(polygonShape->GetVertex(i) + pos));
    // printf("Convex:Point:%d:%f, %f\n", i, convex->getPoint(i).x,
    // convex->getPoint(i).y);
  }
  convex->setFillColor(color);
  // printf("Convex:Pos:%f, %f\n", convex->getPosition().x,
  // convex->getPosition().y);
  return convex;
}

sf::CircleShape *Graphic::GetShape(b2CircleShape *circleShape,
                                   sf::Color color) {
  sf::CircleShape *circle =
      new sf::CircleShape(Math::MeterToPixel(circleShape->m_radius));
  circle->setFillColor(color);
  sf::Vector2f pos = Math::PhysicalCoordSToDrawCoordS(circleShape->m_p);
  circle->setPosition(pos -
                      sf::Vector2f(Math::MeterToPixel(circleShape->m_radius),
                                   Math::MeterToPixel(circleShape->m_radius)));
  return circle;
}

sf::Shape *Graphic::GetShape(b2Fixture *fixture, sf::Color color) {
  b2Body *body = fixture->GetBody();
  b2Shape *shape = fixture->GetShape();
  sf::Shape *shapeS = nullptr;
  switch (shape->GetType()) {
  case b2Shape::e_edge: {

  } break;
  case b2Shape::e_chain: {

  } break;
  case b2Shape::e_circle: {
    b2CircleShape *circleP = static_cast<b2CircleShape *>(shape);
    sf::CircleShape *circleS =
        new sf::CircleShape(Math::MeterToPixel(circleP->m_radius));
    circleS->setFillColor(color);
    circleS->setOrigin(Math::MeterToPixel(circleP->m_radius),
                       Math::MeterToPixel(circleP->m_radius));
    circleS->setPosition(sf::Vector2f(0, 0));
    shapeS = circleS;
  } break;
  case b2Shape::e_polygon: {
    b2PolygonShape *polygonP = static_cast<b2PolygonShape *>(shape);
    sf::ConvexShape *convexS = new sf::ConvexShape();
    convexS->setPointCount(polygonP->GetVertexCount());
    for (int i = 0; i < polygonP->GetVertexCount(); i++) {
      // printf("PolygonShape:Point:%d:%f, %f\n", i, polygonP->GetVertex(i).x,
      // polygonP->GetVertex(i).y);
      convexS->setPoint(
          i, sf::Vector2f(Math::MeterToPixel(
                              body->GetWorldPoint(polygonP->GetVertex(i)).x),
                          Math::MeterToPixel(
                              body->GetWorldPoint(polygonP->GetVertex(i)).y)));
      // printf("Convex:Point:%d:%f, %f\n", i, convexS->getPoint(i).x,
      // convexS->getPoint(i).y);
    }
    convexS->setFillColor(color);
    convexS->setPosition(sf::Vector2f(0, 0));
    shapeS = convexS;
  } break;
  case b2Shape::e_typeCount: {

  } break;
  }
  return shapeS;
}

bool Graphic::isOpen() { return graphic->m_window->isOpen(); }

sf::Vector2u Graphic::getWindowSize() { return graphic->m_window->getSize(); }
