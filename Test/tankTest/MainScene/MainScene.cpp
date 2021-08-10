#include "MainScene.h"
#include <cstdlib>
#include <ctime>
#include "../Body/Entity/Bullet/Bullet.h"
#include "../Body/Item/Weapon/Gun/Gun.h"
#include "../Body/Item/Consume/BulletI/BulletI.h"
#include "../Body/Item/Tool/ArcWelding/ArcWelding.h"
#include "../Body/Item/Tool/CuttingMachine/CuttingMachine.h"
#include "../Body/Item/Tool/NetConnect/NetConnect.h"

#include "../Body/Item/Bag/Bag.h"
#include "../Body/Entity/Biological/Person.h"
#include "../Body/Entity/Box/Box.h"
#include "../Body/Entity/Cube/Cube.h"
#include "../Body/Entity/Thruster/Thruster.h"
#include "../Body/Entity/Computer/Computer.h"

#include "../Body/ItemTManager.h"
#include "../Body/Entity/EntityFactory.h"
#include "../Body/Item/ItemFactory.h"

#define random(a, b) (rand() % (b - a + 1) + a)

/**
 * @brief      Constructs the object.
 */
MainScene::MainScene() : Scene(std::string("MainScene")) {}

/**
 * @brief      Destroys the object.
 */
MainScene::~MainScene()
{
    ItemTManager::Destory();
    EntityFactory::Destroy();
    ItemFactory::Destroy();
}

/**
 * @brief      { Create the object }
 *
 * @return     { this }
 */
MainScene *MainScene::create()
{
    MainScene *scene = new MainScene();
    scene->init();
    return scene;
}

/**
 * @brief      { init the object }
 */
void MainScene::init()
{
    ItemTManager::Create();
    EntityFactory::Create();
    ItemFactory::Create();
    auto physicalWorld =
        this->CreatePhysicalWorld(std::string("World"), false, b2Vec2(0.0f, 0.0f));
    sf::Vector2u windowSize = Graphic::getWindowSize();
    Log::setLevel(LOG_LEVEL_INFO);
    Log::printLog("WindowSize:%d, %d\n", windowSize.x, windowSize.y);
    ResourceManager::LoadFontFromFile(std::string("font/yudit.ttf"), std::string("yudit"));
    ResourceManager::LoadTextureFromFile(std::string("texture/tiepG.png"), std::string("tie"));
    ResourceManager::LoadTextureFromFile(std::string("texture/person.png"), std::string("person"));
    ResourceManager::LoadTextureFromFile(std::string("texture/box.png"), std::string("boxtie"));
    ResourceManager::LoadTextureFromFile(std::string("texture/bullet.png"), std::string("bullet1"));

    // Wall node
    this->GetRootNode()->CreateChild(
    std::string("Wall"), [windowSize, physicalWorld](SNode *node) -> void {
        node->SetPosition(b2Vec2(0, 0));
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
        physicalBody->CreateFixture(std::string("DwonWall"), downfixtureDef);
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
        physicalBody->CreateFixture(std::string("LeftWall"), leftfixtureDef);
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
        physicalBody->CreateFixture(std::string("RightWall"), rightfixtureDef);
    });

    // Ball node
    auto ballNode = this->GetRootNode()->CreateChild(
    std::string("Ball"), [windowSize, physicalWorld](SNode *node) -> void {
        b2Vec2 nodePos =
        Math::DrawCoordSToWorldCoordS(sf::Vector2f(windowSize.x / 2, 40));
        node->SetPosition(nodePos);
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
        // ERROR
        // physicalBody->GetBody()->ApplyLinearImpulseToCenter(b2Vec2(2, 10),
        // true);
        b2CircleShape circleShape;
        // circleShape.m_p = Math::WorldCoordSToPhysicalCoordS(nodePos +
        // localWorldPos); //position, relative to body position
        circleShape.m_p = b2Vec2(0, 0);
        circleShape.m_radius = 1; // radius
        b2FixtureDef fixtureDef;
        fixtureDef.density = 0.1;
        fixtureDef.friction = 0.3;
        fixtureDef.shape = &circleShape;
        fixtureDef.restitution = 1;
        auto fixture =
        physicalBody->CreateFixture(std::string("fixtureBall"), fixtureDef);

        // auto shape = Graphic::GetShape(fixture->GetFixture(), sf::Color(0,
        // 200, 35)); node->InsertShape("MainCircle", shape);
    });

    // Baffle node
    SNode *baffleNode = this->GetRootNode()->CreateChild(
    std::string("Baffle"), [windowSize, physicalWorld](SNode *node) -> void {
        b2Vec2 nodePos = Math::DrawCoordSToWorldCoordS(
            sf::Vector2f(windowSize.x / 2 + 70, windowSize.y / 2));
        node->SetPosition(nodePos);
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
        physicalBody->CreateFixture(std::string("fixtureBaffle"), fixtureDef);
        // auto shape =
        //   Graphic::GetShape(fixture->GetFixture(), sf::Color(0, 0, 125));
        // auto shape = Graphic::GetShape(&polygonShape, bodyDef., sf::Color(0,
        // 0, 125));
        // node->InsertShape("MainRectangle", shape);
    });

    GameObject * root = static_cast<GameObject *>(GetRootNode());

    {
        entityData * data = new entityData("box1", b2Vec2(2, 2));
        data->init = [root, physicalWorld, data](b2Vec2 pos, Entity * mainEntity) -> Entity * {
            b2Vec2 nodePos = pos;
            float angle = 0.0f;
            if (mainEntity != nullptr)
            {
                angle = Math::degreeToRad(data->angle);
                nodePos = PhysicalWorld::generateNodePos(mainEntity->m_physicalBody, data->getSize());
            }
            b2BodyDef bodyDef = PhysicalWorld::generateBodyDef(nodePos, angle);

            b2PolygonShape polygonShape;
            polygonShape.SetAsBox(data->size.x, data->size.y, b2Vec2(0, 0), 0);
            b2FixtureDef fixtureDef = PhysicalWorld::generateFixtureDef(&polygonShape, 0.5, 0.2, 1);

            auto entity = new Box(data->name, root, 100, 100, pos, 100);
            entity->initPhysical(bodyDef, fixtureDef, physicalWorld.get(), "BoxBody", "BoxFixture");
            return entity;
        };
        EntityFactory::addEntity(data);
    }

    {
        entityData * data = new entityData("computer", b2Vec2(2, 2));
        data->init = [root, physicalWorld, data](b2Vec2 pos, Entity * mainEntity) -> Entity * {
            b2Vec2 nodePos = pos;
            float angle = 0.0f;
            if (mainEntity != nullptr)
            {
                angle = Math::degreeToRad(data->angle);
                nodePos = PhysicalWorld::generateNodePos(mainEntity->m_physicalBody, data->getSize());
            }
            b2BodyDef bodyDef = PhysicalWorld::generateBodyDef(nodePos, angle);

            b2PolygonShape polygonShape;
            polygonShape.SetAsBox(data->size.x, data->size.y, b2Vec2(0, 0), 0);
            b2FixtureDef fixtureDef = PhysicalWorld::generateFixtureDef(&polygonShape, 0.5, 0.2, 1);

            auto entity = new Computer(data->name, root, nodePos);
            entity->initPhysical(bodyDef, fixtureDef, physicalWorld.get(), "ComputerBody", "ComputerFixture");
            return entity;
        };
        EntityFactory::addEntity(data);
    }

    {
        entityData * data = new entityData("cubeLittle", b2Vec2(1, 1));
        data->init = [root, physicalWorld, data](b2Vec2 pos, Entity * mainEntity) -> Entity * {
            b2Vec2 nodePos = pos;
            float angle = 0.0f;
            if (mainEntity != nullptr)
            {
                angle = Math::degreeToRad(data->angle);
                nodePos = PhysicalWorld::generateNodePos(mainEntity->m_physicalBody, data->getSize());
            }
            b2BodyDef bodyDef = PhysicalWorld::generateBodyDef(nodePos, angle);

            b2PolygonShape polygonShape;
            polygonShape.SetAsBox(data->size.x, data->size.y, b2Vec2(0, 0), 0);
            b2FixtureDef fixtureDef;
            fixtureDef.density = 0.5;
            fixtureDef.friction = 0.2;
            fixtureDef.restitution = 1;
            fixtureDef.shape = &polygonShape;

            auto entity = new Cube(data->name, root, data->size, pos, 50);
            entity->initPhysical(bodyDef, fixtureDef, physicalWorld.get(), "CubeBody", "CubeFixture");
            return entity;
        };
        EntityFactory::addEntity(data);
    }

    {
        entityData  * data = new entityData("thrusterLittle", b2Vec2(1, 2));
        data->init = [root, physicalWorld, data](b2Vec2 pos, Entity * mainEntity) -> Entity * {
            b2Vec2 nodePos = pos;
            float angle = 0.0f;
            if (mainEntity != nullptr)
            {
                angle = Math::degreeToRad(data->angle) * -1.0f;
                Log::setLevel(LOG_LEVEL_INFO);
                Log::printLog("angle:%f\n", angle);
                nodePos = PhysicalWorld::generateNodePos(mainEntity->m_physicalBody, data->getSize());
            }
            b2BodyDef bodyDef = PhysicalWorld::generateBodyDef(nodePos, angle);

            b2PolygonShape polygonShape;
            polygonShape.SetAsBox(data->size.x, data->size.y, b2Vec2(0, 0), 0);
            b2FixtureDef fixtureDef = PhysicalWorld::generateFixtureDef(&polygonShape);

            auto entity = new Thruster(data->name, root, data->size, 20, pos, 45);
            entity->initPhysical(bodyDef, fixtureDef, physicalWorld.get(), "CubeBody", "CubeFixture");
            return entity;
        };
        EntityFactory::addEntity(data);
    }

    {
        entityData * data = new entityData("bullet", b2Vec2(0.2, 0.2));
        data->init = [root, physicalWorld, data](b2Vec2 pos, Entity * mainEntity) -> Entity * {
            return new Bullet(data->name, root, physicalWorld.get(), pos);
        };
        EntityFactory::addEntity(data);
    }

    ItemFactory::addItem(std::string("gun1"), []() -> Item * {
        return new Gun(std::string("gun1"), 10, 5, 30);
    });

    ItemFactory::addItem(std::string("bag1"), []() -> Item * {
        return new Bag(std::string("bag1"), 10, 10, 300, 300);
    });

    ItemFactory::addItem(std::string("CuttingMachine"), []() -> Item * {
        return new CuttingMachine(std::string("CuttingMachine"), 10, 10);
    });

    ItemFactory::addItem(std::string("ArcWelding"), []() -> Item * {
        return new ArcWelding(std::string("ArcWelding"), 1, 1);
    });

    ItemFactory::addItem(std::string("NetConnect"), []() -> Item * {
        return new NetConnect(std::string("NetConnect"), 1, 1);
    });

    ItemFactory::addItem(std::string("bullet1"), []() -> Item * {
        return new BulletI(std::string("bullet1"), 1, 2);
    });

    // Gun node
    b2Vec2 nodePos = Math::DrawCoordSToPhysicalCoords(sf::Vector2f(windowSize.x / 2, windowSize.y / 2));
    //Gun * gunNode = new Gun(std::string("Gun"), static_cast<GameObject *>(GetRootNode()), physicalWorld.get(), nodePos);
    Person * personNode = new Person(std::string("person"), static_cast<GameObject *>(GetRootNode()), physicalWorld.get(), nodePos);
    personNode->equip(ItemFactory::generateItem(std::string("ArcWelding")));

    Bag * bag = static_cast<Bag *>(ItemFactory::generateItem(std::string("bag1")));
    for (int i = 0; i < 100; i++) {
        bag->addItem(ItemFactory::generateItem(std::string("bullet1")));
    }
    personNode->wearBag(bag);
    Gun * gun = static_cast<Gun *>(ItemFactory::generateItem(std::string("gun1")));
    bag->addItem(gun);
    bag->addItem(ItemFactory::generateItem(std::string("CuttingMachine")));
    bag->addItem(ItemFactory::generateItem(std::string("NetConnect")));

    Box * boxNode = static_cast<Box *>(EntityFactory::generateEntity(std::string("box1"), b2Vec2(0, 10)));
    boxNode->addItem(ItemFactory::generateItem(std::string("bullet1")));
    boxNode->addItem(ItemFactory::generateItem(std::string("bullet1")));
    boxNode->addItem(ItemFactory::generateItem(std::string("gun1")));


    auto camera_pos = this->getCamera().get()->getView().getCenter();
    Log::setLevel(LOG_LEVEL_INFO);
    Log::printLog("ViewPos:%f, %f\n", camera_pos.x, camera_pos.y);
    Log::printLog("baffleNodePos:%f, %f\n", baffleNode->GetPosition().x,
                  baffleNode->GetPosition().y);
    Log::printLog("gunPos:%f, %f\n", personNode->GetPosition().x, personNode->GetPosition().y);
    auto size_view = this->getCamera().get()->getView().getSize();
    Log::printLog("Size:%f, %f\n", size_view.x, size_view.y);
    getCamera().get()->setTrack(personNode, true);

    {
        //b2Vec2 p1(1, 5), p2(3, 3);
        //if (Math::PointInLine(b2Vec2(2, 4), p1, p2)) {
        //Log::printLog("Yes\n");
        //} else {
        //Log::printLog("No\n");
        //}
        b2Vec2 p1(1, 5), p2(3, 3);
        b2Vec2 q1(0, 0), q2(10, 10);
        b2Vec2 result = Math::LinesIntersection(p1, p2, q1, q2);
        Log::printLog("I:%f, %f\n", result.x, result.y);
    }

    SubscribeEventIml(
        E_NODEUPDATEEND,
    [](EventKey key, EventData &data, EventSender *sender) -> void {
        using namespace slt::NodeUpdateBegin;
        //b2Vec2 pos = baffleNode->GetPosition();
    },
    baffleNode, baffleNode->GetName());

    SubscribeEventIml(
        E_NODEUPDATEBEGIN,
    [](EventKey key, EventData &data, EventSender *sender) -> void {
        using namespace slt::NodeUpdateBegin;
        // printf("Sub1:EventName:%s,EventType:%ld\n",
        // slt::EventNameRegistrar::GetEventName(key).c_str(),
        // (long)data[P_TYPE]);
    },
    ballNode, ballNode->GetName());

    SubscribeEventIml(
        E_NODEUPDATEEND,
    [](EventKey key, EventData &data, EventSender *sender) -> void {
        using namespace slt::NodeUpdateEnd;
        // printf("Sub1:EventName:%s,EventType:%ld\n",
        // slt::EventNameRegistrar::GetEventName(key).c_str(),
        // (long)data[P_TYPE]);
    },
    ballNode, ballNode->GetName());

    ballNode->pushUpdateCallBack([this, windowSize](SNode *node) -> void {
        //b2Vec2 pos = node->GetPosition();
        // node->GetPhysicalBody()->GetBody()->SetAwake(true);
        // node->GetPhysicalBody()->GetBody()->ApplyForceToCenter(b2Vec2(0, 1),
        // true);
        // printf("Ball:Pos:%f, %f\n", pos.x, pos.y);
    });

    baffleNode->pushUpdateCallBack([](SNode *node) -> void {
        // printf("Baffle:Pos:%f, %f\n", pos.x, pos.y);
    });

    // this->getCamera().get()->setTrack(baffleNode, true);

    physicalWorld->onBeginContact([](b2Contact *contact) -> void {
        void *userDataA = contact->GetFixtureA()->GetBody()->GetUserData().data[0];
        void *userDataB = contact->GetFixtureB()->GetBody()->GetUserData().data[0];
        if (userDataA && userDataB)
        {
            PhysicalBody *bodyA = static_cast<PhysicalBody *>(userDataA);
            PhysicalBody *bodyB = static_cast<PhysicalBody *>(userDataB);
            std::string::size_type resultA = bodyA->GetName().find("Bullet");
            std::string::size_type resultB = bodyB->GetName().find("Bullet");
            Log::setLevel(LOG_LEVEL_INFO);
            Log::printLog("ContantA:Name:%s\n", bodyA->GetName().c_str());
            Log::printLog("ContantB:Name:%s\n", bodyB->GetName().c_str());

            if (resultA != std::string::npos) {
            }

            if (resultB != std::string::npos) {
                ;
            }
        }
    });

    physicalWorld->onEndContact([this](b2Contact *contact) -> void {
        void *userDataA = contact->GetFixtureA()->GetBody()->GetUserData().data[0];
        void *userDataB = contact->GetFixtureB()->GetBody()->GetUserData().data[0];
        if (userDataA && userDataB)
        {
            PhysicalBody *bodyA = static_cast<PhysicalBody *>(userDataA);
            PhysicalBody *bodyB = static_cast<PhysicalBody *>(userDataB);
            std::string::size_type resultA = bodyA->GetName().find("BulletBody");
            std::string::size_type resultB = bodyB->GetName().find("BulletBody");
            Bullet * bulletNode = nullptr;
            if (resultA != std::string::npos) {
                bulletNode = static_cast<Bullet *>(bodyA->GetBody()->GetUserData().data[1]);
            }

            if (resultB != std::string::npos) {
                bulletNode = static_cast<Bullet *>(bodyB->GetBody()->GetUserData().data[1]);
            }
            if (bulletNode != nullptr) {
                bulletNode->setHp(0);
            }
            //GetRootNode()->DeleteChild(bulletNode->GetName());
        }

    });

    float force = 5;

    // bind key callBack
    Graphic::insertKeyCallBack(sf::Keyboard::Key::W, [personNode, force]() -> void {
        // printf("Move:Left\n");
        // baffleNode->move(b2Vec2(-2, 0));
        //personNode->GetPhysicalBody()->GetBody()->ApplyLinearImpulseToCenter(b2Vec2(-force, 0), true);
        personNode->move(0, force);
    });
    Graphic::insertKeyCallBack(sf::Keyboard::Key::S, [personNode, force]() -> void {
        // printf("Move:Right\n");
        //personNode->GetPhysicalBody()->GetBody()->ApplyLinearImpulseToCenter(b2Vec2(force, 0), true);
        // baffleNode->move(b2Vec2(2, 0));
        personNode->move(1, force);
    });
    Graphic::insertKeyCallBack(sf::Keyboard::Key::A, [personNode, force]() -> void {
        // printf("Move:Up\n");
        // baffleNode->move(b2Vec2(0, 2));
        //personNode->GetPhysicalBody()->GetBody()->ApplyLinearImpulseToCenter(b2Vec2(0, force), true);
        personNode->move(2, force);
    });
    Graphic::insertKeyCallBack(sf::Keyboard::Key::D, [personNode, force]() -> void {
        // printf("Move:Down\n");
        // baffleNode->move(b2Vec2(0, -2));
        //personNode->GetPhysicalBody()->GetBody()->ApplyLinearImpulseToCenter(b2Vec2(0, -force), true);
        personNode->move(3, force);
    });
    Graphic::insertKeyCallBack(sf::Keyboard::Key::R, [personNode]() -> void {
        if (personNode->handP())
        {
            if (personNode->getHand()->getTypeName() == std::string("Weapon")) {
                Gun * gun = static_cast<Gun*>(personNode->getHand());
                if (!gun->isLoadFull()) {
                    Bag * bag = personNode->getBag();
                    std::vector<Item *> bullets = bag->getItem(std::string("bullet1"), 30);
                    for (int i = 0; i < (int)bullets.size(); i++) {
                        gun->loadBullet(static_cast<BulletI *>(bullets[i]));
                    }
                }
            } else if (personNode->getHand()->getTypeName() == std::string("Tool")) {
                Tool * tool = static_cast<Tool*>(personNode->getHand());
                if (tool->getName() == "ArcWelding") {
                    ArcWelding * arcWelding = static_cast<ArcWelding *>(tool);
                    auto generateEntity = arcWelding->m_generateEntity;
                    entityData * generateData = EntityFactory::getEntityData(generateEntity);
                    Log::setLevel(LOG_LEVEL_INFO);
                    if (generateData->angle == 360) {
                        generateData->angle = 90;
                        Log::printLog("gui\n");
                    } else {
                        generateData->angle += 90;
                        Log::printLog("increase\n");
                    }
                    Log::printLog("[%s]data:%d\n", generateEntity.c_str(), generateData->angle);
                }
            }
        }
    });
    Graphic::insertKeyCallBack(sf::Keyboard::E, [personNode, physicalWorld]() -> void {
        personNode->useFace(physicalWorld.get());
    });
    Graphic::insertKeyCallBack(sf::Keyboard::Tab, [personNode, physicalWorld]() -> void {
        personNode->SetDrawUi(!personNode->GetDrawUi());
    });
    Graphic::insertMouseClickCallBack(
    sf::Mouse::Left, [personNode, physicalWorld](sf::Vector2i pos) -> void {
        //printf("Left:MousePos:%d, %d\n", pos.x, pos.y);
        //Temporary
        if (!Graphic::isMouseInWindow())
        {
            sf::Vector2f coordPos = Graphic::PixelToCoords(pos);
            personNode->useHand(Math::DrawCoordSToPhysicalCoords(coordPos));
        }
    });

    Graphic::insertMouseClickCallBack(sf::Mouse::Right, [personNode](sf::Vector2i pos) -> void {
        if (!Graphic::isMouseInWindow())
        {
            sf::Vector2f coordPos = Graphic::PixelToCoords(pos);
            personNode->rightClick(Math::DrawCoordSToWorldCoordS(coordPos));
        }
    });

    // Shoot bullet
    // Graphic::insertKeyCallBack(
    //     sf::Keyboard::Key::Space,
    // [gunNode, windowSize, physicalWorld, this]() -> void {
    //     gunNode->fire(GetRootNode(), physicalWorld.get());
    // });

    Graphic::insertKeyCallBack(sf::Keyboard::Key::Escape, []() -> void { Graphic::Close(); });

    Graphic::insertKeyCallBack(sf::Keyboard::Key::H,
    [this]() -> void {
        // printf("Move:Left\n");
        this->getCamera().get()->move(-2, 0);
    });
    Graphic::insertKeyCallBack(sf::Keyboard::Key::L,
    [this]() -> void {
        // printf("Move:Right\n");
        this->getCamera().get()->move(2, 0);
    });
    Graphic::insertKeyCallBack(sf::Keyboard::Key::J,
    [this]() -> void {
        // printf("Move:Up\n");
        this->getCamera().get()->move(0, 2);
    });
    Graphic::insertKeyCallBack(sf::Keyboard::Key::K,
    [this]() -> void {
        // printf("Move:Down\n");
        this->getCamera().get()->move(0, -2);
    });
    Graphic::insertKeyCallBack(
    sf::Keyboard::Key::P, [this, baffleNode, ballNode]() -> void {
        auto pos_view = this->getCamera().get()->getView().getCenter();
        auto size_view = this->getCamera().get()->getView().getSize();
        Log::setLevel(LOG_LEVEL_INFO);
        Log::printLog("viewPos:%f, %f;Size:%f, %f\n", pos_view.x, pos_view.y,
                      size_view.x, size_view.y);
        auto pos_baffle = baffleNode->GetPosition();
        Log::printLog("bafflePos:%f, %f\n", pos_baffle.x, pos_baffle.y);
        auto linearVelocity =
        ballNode->GetPhysicalBody()->GetBody()->GetLinearVelocity();
        Log::printLog("ballNodeSpedd:%f\n", linearVelocity.Length());
    });
    Graphic::insertKeyCallBack(sf::Keyboard::Key::F, [this, ballNode]() -> void {
        ballNode->GetPhysicalBody()->GetBody()->ApplyLinearImpulseToCenter(
            b2Vec2(0, -10), true);
    });
    Graphic::insertKeyCallBack(sf::Keyboard::Key::N, [this]() -> void {
        this->getCamera()->zoom(1.1f);
    });
    Graphic::insertKeyCallBack(sf::Keyboard::Key::B, [this]() -> void {
        this->getCamera()->zoom(1.0f);
    });
    Graphic::insertKeyCallBack(sf::Keyboard::Key::M, [this]() -> void {
        this->getCamera()->zoom(0.9f);
    });
    // Graphic::insertKeyCallBack(sf::Keyboard::Key::G, [this, gunNode]() -> void {
    //     auto pos = this->GetRootNode()->GetChild(std::string("Gun"))->GetPosition();
    //     printf("gunNode:%f %f\n", pos.x, pos.y);
    // });
    Graphic::insertMouseWheelCallBack(
    [this](sf::Event::MouseWheelScrollEvent event) -> void {
        if (!Graphic::isMouseInWindow())
        {
            int delta = event.delta;
            if (delta > 0) {
                this->getCamera()->zoom(0.9);
            } else {
                this->getCamera()->zoom(1.1);
            }
        }
    });
    Graphic::insertKeyCallBack(sf::Keyboard::Key::C, []() -> void {
        Log::setDrawUi();
    });
    Graphic::insertKeyCallBack(sf::Keyboard::Key::V, []() -> void {
        Script::setDrawUi();
    });
    DEFUN_NONE("hello", []() -> void {
        Log::setLevel(LOG_LEVEL_INFO);
        Log::printLog("print\n");
    })
    cl_object (*generateEntity)(cl_object, int, int) = [](cl_object name, int x, int y) -> cl_object {
        Log::setLevel(LOG_LEVEL_INFO);
        std::string nameC = Script::clToString(name);
        Log::printLog("EntityName:%s, %f, %f\n", nameC.c_str(), x, y);
        EntityFactory::generateEntity(nameC, b2Vec2(x, y));
        return ECL_NIL;
    };
    DEFUN("generateEntity", generateEntity, 3);
}

void MainScene::DrawUiSelf()
{
    ImGui::ShowDemoWindow();
}

/**
 * @brief      { update self in one of dt }
 *
 * @param      dt    { The dalate time }
 */
void MainScene::UpdateSelf(sf::Time &dt)
{

    //printf("RunUpdae\n");
    //auto pos = this->GetRootNode()->GetChild("Gun")->GetPosition();
    b2Vec2 pos(0, 0);
    auto ballPos = this->GetRootNode()->GetChild("Ball")->GetPosition();
    // auto pixel_pos = Graphic::getInstance()->worldToPixel(sf::Vector2f(pos.x,
    // pos.y)); auto pixel_pos = Math::WorldCoordSToDrawCoordS(pos);
    // Graphic::getInstance()->getCamera(std::string("Main")).get()->setPosition(sf::Vector2f(pixel_pos.x,
    // pixel_pos.y));
    // Graphic::getInstance()->getCamera(std::string("Main")).get()->setSize(sf::Vector2f(800.f,
    // 700.f));
    auto g = this->GetPhysicalWorld().get()->GetGravity();
    auto text = new sf::Text();
    text->setFont(*ResourceManager::GetFont("yudit"));
    text->setString(std::string("gunPos:") + std::to_string(pos.x) + ", " +
                    std::to_string(pos.y) + "\n" + "G:" + std::to_string(g.x) +
                    "," + std::to_string(g.y) + "\n" + std::string("BallPos") +
                    std::to_string(ballPos.x) + ", " + std::to_string(ballPos.y));
    text->setCharacterSize(24); // in pixels, not points!
    text->setFillColor(sf::Color::Red);
    text->setPosition(10.f, 20.f);
    text->setStyle(sf::Text::Bold | sf::Text::Underlined);
    Graphic::insert(text);

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
