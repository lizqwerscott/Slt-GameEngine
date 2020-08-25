#include "MainScene.h"
#include <cstdlib>
#include <ctime>
#define random(a, b) (rand() % (b - a + 1) + a)

/**
 * @brief      Constructs the object.
 */
MainScene::MainScene() : Scene(std::string("MainScene")) {}

/**
 * @brief      Destroys the object.
 */
MainScene::~MainScene() {}

/**
 * @brief      { Create the object }
 *
 * @return     { this }
 */
MainScene *MainScene::create() {
  MainScene *scene = new MainScene();
  scene->init();
  return scene;
}

/**
 * @brief      { init the object }
 */
void MainScene::init() {
  auto physicalWorld =
      this->CreatePhysicalWorld(std::string("World"), true, b2Vec2(0, 0));
  sf::Vector2u windowSize = Graphic::getWindowSize();
  printf("WindowSize:%d, %d\n", windowSize.x, windowSize.y);
  ResourceManager::LoadFontFromFile(
      std::string(
          "/home/lizqwer/project/Slt-GameEngine/resource/font/yudit.ttf"),
      std::string("yudit"));

  // Wall node
  this->GetRootNode()->CreateChild(
      std::string("Wall"), [windowSize, physicalWorld](SNode *node) -> void {
        node->SetPosation(b2Vec2(0, 0));
        // Create Body
        b2BodyDef bodyDef;
        bodyDef.type = b2BodyType::b2_staticBody;
        bodyDef.position = b2Vec2(0, 0);
        bodyDef.angle = 0;
        auto physicalBody =
            node->CreatePhysicalBody(std::string("WallBody"), b2Vec2(0, 0),
                                     bodyDef, physicalWorld.get());
        // Fixture

        // Up Wall
        b2FixtureDef upfixtureDef;
        upfixtureDef.density = 1;
        upfixtureDef.friction = 0;
        upfixtureDef.restitution = 1;
        b2Vec2 upLocalWorldPos(Math::DrawCoordSToPhysicalCoords(
            sf::Vector2f(windowSize.x / 2, 0)));
        b2PolygonShape upPolygonShape;
        upPolygonShape.SetAsBox(
            Math::PixelToMeter(windowSize.x / 2), 1,
            Math::WorldCoordSToPhysicalCoordS(upLocalWorldPos), 0);
        upfixtureDef.shape = &upPolygonShape;
        physicalBody->CreateFixture(std::string("UpWall"), upfixtureDef);
        // Down Wall
        b2FixtureDef downfixtureDef;
        downfixtureDef.density = 1;
        downfixtureDef.friction = 0;
        downfixtureDef.restitution = 1;
        b2Vec2 downLocalWorldPos(Math::DrawCoordSToPhysicalCoords(
            sf::Vector2f(windowSize.x / 2, windowSize.y)));
        b2PolygonShape downPolygonShape;
        downPolygonShape.SetAsBox(
            Math::PixelToMeter(windowSize.x / 2), 1,
            Math::WorldCoordSToPhysicalCoordS(downLocalWorldPos), 0);
        downfixtureDef.shape = &downPolygonShape;
        physicalBody->CreateFixture(std::string("UpWall"), downfixtureDef);
        // Left Wall
        b2FixtureDef leftfixtureDef;
        leftfixtureDef.density = 1;
        leftfixtureDef.friction = 0;
        leftfixtureDef.restitution = 1;
        b2Vec2 leftLocalWorldPos(Math::DrawCoordSToPhysicalCoords(
            sf::Vector2f(0, windowSize.y / 2)));
        b2PolygonShape leftPolygonShape;
        leftPolygonShape.SetAsBox(
            1, Math::PixelToMeter(windowSize.y / 2),
            Math::WorldCoordSToPhysicalCoordS(leftLocalWorldPos), 0);
        leftfixtureDef.shape = &leftPolygonShape;
        physicalBody->CreateFixture(std::string("UpWall"), leftfixtureDef);
        // Right Wall
        b2FixtureDef rightfixtureDef;
        rightfixtureDef.density = 1;
        rightfixtureDef.friction = 0;
        rightfixtureDef.restitution = 1;
        b2Vec2 rightLocalWorldPos(Math::DrawCoordSToPhysicalCoords(
            sf::Vector2f(windowSize.x, windowSize.y / 2)));
        b2PolygonShape rightPolygonShape;
        rightPolygonShape.SetAsBox(
            1, Math::PixelToMeter(windowSize.y / 2),
            Math::WorldCoordSToPhysicalCoordS(rightLocalWorldPos), 0);
        rightfixtureDef.shape = &rightPolygonShape;
        physicalBody->CreateFixture(std::string("UpWall"), rightfixtureDef);
      });

  // Ball node
  auto ballNode = this->GetRootNode()->CreateChild(
      std::string("Ball"), [windowSize, physicalWorld](SNode *node) -> void {
        b2Vec2 nodePos =
            Math::DrawCoordSToWorldCoordS(sf::Vector2f(windowSize.x / 2, 0));
        node->SetPosation(nodePos);
        b2Vec2 localWorldPos(0, 0);

        b2BodyDef bodyDef;
        bodyDef.type = b2BodyType::b2_dynamicBody;
        bodyDef.position =
            Math::WorldCoordSToPhysicalCoordS(nodePos + localWorldPos);
        bodyDef.angle = 0;
        bodyDef.bullet = true;
        auto physicalBody =
            node->CreatePhysicalBody(std::string("BallBody"), localWorldPos,
                                     bodyDef, physicalWorld.get());
        physicalBody->GetBody()->ApplyLinearImpulse(
            b2Vec2(random(1, 10) * random(1, 5), random(1, 10) * random(1, 5)),
            b2Vec2(0, 0), true);

        b2CircleShape circleShape;
        // circleShape.m_p = Math::WorldCoordSToPhysicalCoordS(nodePos +
        // localWorldPos); //position, relative to body position
        circleShape.m_p = b2Vec2(0, 0);
        circleShape.m_radius = 1; // radius
        b2FixtureDef fixtureDef;
        fixtureDef.density = 0.1;
        fixtureDef.friction = 0;
        fixtureDef.shape = &circleShape;
        fixtureDef.restitution = 1;
        auto fixture =
            physicalBody->CreateFixture(std::string("fixture"), fixtureDef);

        auto shape =
            Graphic::GetShape(fixture->GetFixture(), sf::Color(0, 200, 35));
        node->InsertShape("MainCircle", shape);
      });

  // Baffle node
  SNode *baffleNode = this->GetRootNode()->CreateChild(
      std::string("Baffle"), [windowSize, physicalWorld](SNode *node) -> void {
        b2Vec2 nodePos = Math::DrawCoordSToWorldCoordS(
            sf::Vector2f(windowSize.x / 2, windowSize.y / 2));
        node->SetPosation(nodePos);
        b2Vec2 localWorldPos(0, 0);
        b2BodyDef bodyDef;
        bodyDef.type = b2BodyType::b2_kinematicBody;
        bodyDef.position =
            Math::WorldCoordSToPhysicalCoordS(nodePos + localWorldPos);
        bodyDef.angle = 0;
        bodyDef.bullet = true;
        auto physicalBody =
            node->CreatePhysicalBody(std::string("BaffleBody"), localWorldPos,
                                     bodyDef, physicalWorld.get());
        b2PolygonShape polygonShape;
        // polygonShape.SetAsBox(3, 1, Math::WorldCoordSToPhysicalCoordS(nodePos
        // + localWorldPos), 0);
        polygonShape.SetAsBox(3, 1, b2Vec2(0, 0), 0);
        b2FixtureDef fixtureDef;
        fixtureDef.density = 1;
        fixtureDef.friction = 0;
        fixtureDef.restitution = 1;
        fixtureDef.shape = &polygonShape;
        auto fixture =
            physicalBody->CreateFixture(std::string("fixture"), fixtureDef);
        auto shape =
            Graphic::GetShape(fixture->GetFixture(), sf::Color(0, 0, 125));
        // auto shape = Graphic::GetShape(&polygonShape, bodyDef., sf::Color(0,
        // 0, 125));
        node->InsertShape("MainRectangle", shape);
      });
  auto camera = Graphic::getInstance()->getCamera(std::string("Main"));
  auto camera_pos = camera->getView().getCenter();
  printf("ViewPos:%f, %f", camera_pos.x, camera_pos.y);
  auto worview_pos = Graphic::getInstance()->worldToPixel(sf::Vector2f(0.f, 0.f));
  printf("converPos:%i, %i", worview_pos.x, worview_pos.y);

  SubscribeEventIml(
      E_NODEUPDATEEND,
      [baffleNode](EventKey key, EventData & data, EventSender * sender) -> void {
        using namespace slt::NodeUpdateBegin;
        b2Vec2 pos = baffleNode->GetPosation();
        auto pixel_pos = Graphic::getInstance()->worldToPixel(sf::Vector2f(pos.x, pos.y));
        //printf("converPos:%i, %i", pixel_pos.x, pixel_pos.y);
        //Graphic::getInstance()->getCamera(std::string("Main")).get()->setPosition(sf::Vector2f(pixel_pos.x, pixel_pos.y));
      },
      baffleNode);

  SubscribeEventIml(
      E_NODEUPDATEBEGIN,
      [](EventKey key, EventData & data, EventSender *sender) -> void {
        using namespace slt::NodeUpdateBegin;
        // printf("Sub1:EventName:%s,EventType:%ld\n",
        // slt::EventNameRegistrar::GetEventName(key).c_str(),
        // (long)data[P_TYPE]);
      },
      ballNode);

  SubscribeEventIml(
      E_NODEUPDATEEND,
      [](EventKey key, EventData &data, EventSender *sender) -> void {
        using namespace slt::NodeUpdateEnd;
        // printf("Sub1:EventName:%s,EventType:%ld\n",
        // slt::EventNameRegistrar::GetEventName(key).c_str(),
        // (long)data[P_TYPE]);
      },
      ballNode);

  ballNode->pushUpdateCallBack([this, windowSize](SNode *node) -> void {
    b2Vec2 pos = node->GetPosation();
    // printf("Ball:Pos:%f, %f\n", pos.x, pos.y);
  });

  baffleNode->pushUpdateCallBack([](SNode *node) -> void {
    // printf("Baffle:Pos:%f, %f\n", pos.x, pos.y);
  });

  physicalWorld->onBeginContact([](b2Contact *contact) -> void {
    void *userDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void *userDataB = contact->GetFixtureB()->GetBody()->GetUserData();
    if (userDataA && userDataB) {
      PhysicalBody *bodyA = static_cast<PhysicalBody *>(userDataA);
      PhysicalBody *bodyB = static_cast<PhysicalBody *>(userDataB);
      if (bodyA->GetName() == "Ball") {

      } else if (bodyB->GetName() == "Ball") {
      }
    }
  });

  physicalWorld->onEndContact([](b2Contact *contact) -> void {

  });

  // bind key callBack
  Graphic::insertKeyCallBack(sf::Keyboard::Key::Left, [baffleNode]() -> void {
    // printf("Move:Left\n");
    baffleNode->move(b2Vec2(-2, 0));
  });
  Graphic::insertKeyCallBack(sf::Keyboard::Key::Right, [baffleNode]() -> void {
    // printf("Move:Right\n");
    baffleNode->move(b2Vec2(2, 0));
  });
  Graphic::insertKeyCallBack(sf::Keyboard::Key::Up, [baffleNode]() -> void {
    // printf("Move:Up\n");
    baffleNode->move(b2Vec2(0, 2));
  });
  Graphic::insertKeyCallBack(sf::Keyboard::Key::Down, [baffleNode]() -> void {
    // printf("Move:Down\n");
    baffleNode->move(b2Vec2(0, -2));
  });
  Graphic::insertKeyCallBack(sf::Keyboard::Key::Escape,
                             []() -> void { Graphic::Close(); });

  Graphic::insertKeyCallBack(sf::Keyboard::Key::H, [baffleNode]() -> void {
    // printf("Move:Left\n");
    Graphic::getInstance()->getCamera(std::string("Main")).get()->move(-2, 0);
  });
  Graphic::insertKeyCallBack(sf::Keyboard::Key::L, [baffleNode]() -> void {
    // printf("Move:Right\n");
    Graphic::getInstance()->getCamera(std::string("Main")).get()->move(2, 0);
  });
  Graphic::insertKeyCallBack(sf::Keyboard::Key::J, [baffleNode]() -> void {
    // printf("Move:Up\n");
    Graphic::getInstance()->getCamera(std::string("Main")).get()->move(0, 2);
  });
  Graphic::insertKeyCallBack(sf::Keyboard::Key::K, [baffleNode]() -> void {
    // printf("Move:Down\n");
    Graphic::getInstance()->getCamera(std::string("Main")).get()->move(0, -2);
  });
  Graphic::insertKeyCallBack(sf::Keyboard::Key::P, [baffleNode]() -> void {
    auto pos = Graphic::getInstance()->getCamera(std::string("Main")).get()->getView().getCenter();
    printf("viewPos:%f, %f\n", pos.x, pos.y);
  });

  /*
  srand((unsigned)time(NULL));
  speed = b2Vec2(random(1, 10), random(1, 10));
  ballNode->pushUpdateCallBack([this, baffleNode, windowSize](SNode *
  node)->void { b2Vec2 ballPos = node->GetPosation(); sf::CircleShape *
  ballShape = dynamic_cast<sf::CircleShape
  *>(node->GetShape("MainCircle").get());
      //Collision in wall
              //judgment ball collision with upWall?
      {
              if (ballPos.y <= 0)
              {
                      printf("Up\n");
                      speed = b2Vec2(speed.x, -speed.y);
              }
      }
      //judgment ball collision with downWall?
      {
              if (ballPos.y - ballShape->getRadius() * 2 >= windowSize.y)
              {
                      printf("Down\n");
                      speed = b2Vec2(speed.x, -speed.y);
              }
      }
      //judgment ball collision with leftWall?
      {
              if (ballPos.x <= 0)
              {
                      printf("Left\n");
                      speed = b2Vec2(-speed.x, speed.y);
              }
      }
      //judgment ball collision with rightWall?
      {
              if (ballPos.x - ballShape->getRadius() * 2 >= windowSize.x)
              {
                      printf("Right\n");
                      speed = b2Vec2(-speed.x, speed.y);
              }
      }
      //judgment ball collision with baffle?
      {
              //sf::RectangleShape * rectangleShape =
  dynamic_cast<sf::RectangleShape
  *>(baffleNode->GetShape("MainRectangle").get());
              //b2Vec2 bafflePos = baffleNode->GetPosation();
              //if true
              ;
      }
      //judgment ball collision with Bricks? ......
      {

      }
      //printf("Speed:%f, %f\n", speed.x, speed.y);
      b2Vec2 movePos(speed.x + node->GetPosation().x, abs(speed.y -
  node->GetPosation().y));
      //printf("MovePos:%f, %f\n", movePos.x, movePos.y);
      node->SetPosation(movePos);
  });
  */
}

/**
 * @brief      { update self in one of dt }
 *
 * @param      dt    { The dalate time }
 */
void MainScene::UpdateSelf(sf::Time &dt) {
  // sf::Vector2u windowSize = Graphic::getWindowSize();
  auto text = new sf::Text();
  text->setFont(*ResourceManager::GetFont("yudit"));
  text->setString(std::string("hello"));
  text->setCharacterSize(24); // in pixels, not points!
  text->setFillColor(sf::Color::Red);
  text->setPosition(10.f, 20.f);
  text->setStyle(sf::Text::Bold | sf::Text::Underlined);
  Graphic::insert(text);

  auto pos = this->GetRootNode()->GetChild("Baffle")->GetPosation();
  auto pixel_pos = Graphic::getInstance()->worldToPixel(sf::Vector2f(pos.x, pos.y));
  //Graphic::getInstance()->getCamera(std::string("Main")).get()->setPosition(sf::Vector2f(pixel_pos.x, pixel_pos.y));
  //Graphic::getInstance()->getCamera(std::string("Main")).get()->setPosition(sf::Vector2f(400.f, 350.f));
  
  // Graphic::getInstance()->DrawCircle(b2Vec2(0, 0), 2, b2Color(1, 0, 0));
  // Graphic::getInstance()->DrawPolygon();
  /*
  b2Vec2 vertices[3];
  vertices[0] = b2Vec2(0, 10);
  vertices[1] = b2Vec2(10, 0);
  vertices[2] = b2Vec2(-10, 0);
  Graphic::getInstance()->DrawPolygon(&vertices[0], 3, b2Color(0, 1, 0));
  Graphic::getInstance()->DrawCircle(b2Vec2(0, 0), 2, b2Color(1, 0, 0));
  Graphic::getInstance()->DrawPoint(b2Vec2(0, 0), 2, b2Color(0, 0, 0));
  */
}
