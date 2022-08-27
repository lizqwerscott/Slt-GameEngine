#include "MainScene.h"
#include "../Body/Entity/AllEntity.h"
#include "../Body/Item/AllItem.h"
#include <cstdlib>
#include <ctime>

#include "../Body/ItemTManager.h"
#include "ResourceManager/ResourceManager.h"

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
    auto physicalWorld = this->CreatePhysicalWorld(std::string("World"), false,
                         b2Vec2(0.0f, 0.0f));
    sf::Vector2u windowSize = Graphic::getWindowSize();
    Log::setLevel(LOG_LEVEL_INFO);
    Log::printLog("WindowSize:%d, %d\n", windowSize.x, windowSize.y);
    // ResourceManager::LoadFontFromFile("yudit.ttf", "yudit");
    ResourceManager::LoadFontFromFile("odokai.ttf", "odokai");

    ResourceManager::LoadTextureFromFile("tiepG.png", "tie");
    ResourceManager::LoadTextureFromFile("person.png", "person");
    ResourceManager::LoadTextureFromFile("box.png", "boxtie");
    ResourceManager::LoadTextureFromFile("bullet.png", "bullet1");
    ResourceManager::LoadTextureFromFile("computer.png", "computer");
    ResourceManager::LoadTextureFromFile("seat.png", "seat");
    ResourceManager::LoadTextureFromFile("thruster.png", "thruster");
    ResourceManager::LoadTextureFromFile("generator.png", "generator");
    ResourceManager::LoadTextureFromFile("wireTie.png", "wireTie");
    ResourceManager::LoadTextureFromFile("energyTie.png", "energyTie");
    ResourceManager::LoadTextureFromFile("energyCWire.png", "energyCWire");
    ResourceManager::LoadTextureFromFile("gyro.png", "gyro");

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

    GameObject *root = static_cast<GameObject *>(GetRootNode());

    {
        entityData *data = new entityData("box1", b2Vec2(2, 2));
        data->init = [root, physicalWorld, data](b2Vec2 pos,
        Entity *mainEntity) -> Entity * {
            b2Vec2 nodePos = pos;
            float angle = 0.0f;
            if (mainEntity != nullptr)
            {
                angle = mainEntity->GetAngle() + data->getAngle();
                auto faceEntityData =
                EntityFactory::getEntityData(mainEntity->GetName());
                nodePos = PhysicalWorld::generateNodePos(mainEntity->m_physicalBody,
                        faceEntityData->getSize(),
                        data->getSize());
            }
            b2BodyDef bodyDef = PhysicalWorld::generateBodyDef(nodePos, angle);

            b2PolygonShape polygonShape;
            polygonShape.SetAsBox(data->size.x, data->size.y, b2Vec2(0, 0), 0);
            b2FixtureDef fixtureDef =
            PhysicalWorld::generateFixtureDef(&polygonShape, 0.5, 0.2, 1);

            auto entity = new Box(data->name, root, 100, 100, pos, 100);
            entity->initPhysical(bodyDef, fixtureDef, physicalWorld.get(), "BoxBody",
                                 "BoxFixture");
            return entity;
        };
        EntityFactory::addEntity(data);
    }

    {
        entityData *data = new entityData("computer", b2Vec2(1, 1));
        data->init = [root, physicalWorld, data](b2Vec2 pos,
        Entity *mainEntity) -> Entity * {
            b2Vec2 nodePos = pos;
            float angle = 0.0f;
            if (mainEntity != nullptr)
            {
                angle = mainEntity->GetAngle() + data->getAngle();
                auto faceEntityData =
                EntityFactory::getEntityData(mainEntity->GetName());
                nodePos = PhysicalWorld::generateNodePos(mainEntity->m_physicalBody,
                        faceEntityData->getSize(),
                        data->getSize());
            }
            b2BodyDef bodyDef = PhysicalWorld::generateBodyDef(nodePos, angle);

            b2PolygonShape polygonShape;
            polygonShape.SetAsBox(data->size.x, data->size.y, b2Vec2(0, 0), 0);
            b2FixtureDef fixtureDef =
            PhysicalWorld::generateFixtureDef(&polygonShape, 0.5, 0.2, 1);

            auto entity = new Computer(data->name, root, nodePos);
            entity->initPhysical(bodyDef, fixtureDef, physicalWorld.get(),
                                 "ComputerBody", "ComputerFixture");
            return entity;
        };
        EntityFactory::addEntity(data);
    }

    {
        entityData *data = new entityData("seat", b2Vec2(1, 3));
        data->init = [root, physicalWorld, data](b2Vec2 pos,
        Entity *mainEntity) -> Entity * {
            b2Vec2 nodePos = pos;
            float angle = 0.0f;
            if (mainEntity != nullptr)
            {
                angle = mainEntity->GetAngle() + data->getAngle();
                auto faceEntityData =
                EntityFactory::getEntityData(mainEntity->GetName());
                nodePos = PhysicalWorld::generateNodePos(mainEntity->m_physicalBody,
                        faceEntityData->getSize(),
                        data->getSize());
            }
            b2BodyDef bodyDef = PhysicalWorld::generateBodyDef(nodePos, angle);

            b2PolygonShape polygonShape;
            polygonShape.SetAsBox(data->size.x, data->size.y, b2Vec2(0, 0), 0);
            b2FixtureDef fixtureDef =
            PhysicalWorld::generateFixtureDef(&polygonShape, 0.5, 0.2, 1);

            auto entity = new Seat(data->name, root, nodePos);
            entity->initPhysical(bodyDef, fixtureDef, physicalWorld.get(), "SeatBody",
                                 "SeatFixture");
            return entity;
        };
        EntityFactory::addEntity(data);
    }

    {
        entityData *data = new entityData("cubeLittle", b2Vec2(1, 1));
        data->init = [root, physicalWorld, data](b2Vec2 pos,
        Entity *mainEntity) -> Entity * {
            b2Vec2 nodePos = pos;
            float angle = 0.0f;
            if (mainEntity != nullptr)
            {
                angle = mainEntity->GetAngle() + data->getAngle();
                auto faceEntityData =
                EntityFactory::getEntityData(mainEntity->GetName());
                nodePos = PhysicalWorld::generateNodePos(mainEntity->m_physicalBody,
                        faceEntityData->getSize(),
                        data->getSize());
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
            entity->initPhysical(bodyDef, fixtureDef, physicalWorld.get(), "CubeBody",
                                 "CubeFixture");
            return entity;
        };
        EntityFactory::addEntity(data);
    }

    {
        entityData *data = new entityData("cubeWire", b2Vec2(1, 2));
        data->init = [root, physicalWorld, data](b2Vec2 pos,
        Entity *mainEntity) -> Entity * {
            b2Vec2 nodePos = pos;
            float angle = 0.0f;
            if (mainEntity != nullptr)
            {
                angle = mainEntity->GetAngle() + data->getAngle();
                auto faceEntityData =
                EntityFactory::getEntityData(mainEntity->GetName());
                nodePos = PhysicalWorld::generateNodePos(mainEntity->m_physicalBody,
                        faceEntityData->getSize(),
                        data->getSize());
            }
            b2BodyDef bodyDef = PhysicalWorld::generateBodyDef(nodePos, angle);

            b2PolygonShape polygonShape;
            polygonShape.SetAsBox(data->size.x, data->size.y, b2Vec2(0, 0), 0);
            b2FixtureDef fixtureDef;
            fixtureDef.density = 0.5;
            fixtureDef.friction = 0.2;
            fixtureDef.restitution = 1;
            fixtureDef.shape = &polygonShape;

            auto entity = new CubeWire(data->name, root, data->size, pos, 50);
            entity->initPhysical(bodyDef, fixtureDef, physicalWorld.get(),
                                 "CubeWireBody", "CubeWireFixture");
            return entity;
        };
        EntityFactory::addEntity(data);
    }

    {
        entityData *data = new entityData("cubeEnergyWire", b2Vec2(1, 2));
        data->init = [root, physicalWorld, data](b2Vec2 pos,
        Entity *mainEntity) -> Entity * {
            b2Vec2 nodePos = pos;
            float angle = 0.0f;
            if (mainEntity != nullptr)
            {
                angle = mainEntity->GetAngle() + data->getAngle();
                auto faceEntityData =
                EntityFactory::getEntityData(mainEntity->GetName());
                nodePos = PhysicalWorld::generateNodePos(mainEntity->m_physicalBody,
                        faceEntityData->getSize(),
                        data->getSize());
            }
            b2BodyDef bodyDef = PhysicalWorld::generateBodyDef(nodePos, angle);

            b2PolygonShape polygonShape;
            polygonShape.SetAsBox(data->size.x, data->size.y, b2Vec2(0, 0), 0);
            b2FixtureDef fixtureDef;
            fixtureDef.density = 0.5;
            fixtureDef.friction = 0.2;
            fixtureDef.restitution = 1;
            fixtureDef.shape = &polygonShape;

            auto entity = new CubeEnergyWire(data->name, root, data->size, pos, 50);
            entity->initPhysical(bodyDef, fixtureDef, physicalWorld.get(),
                                 "CubeEnergyWireBody", "CubeEnergyWireFixture");
            return entity;
        };
        EntityFactory::addEntity(data);
    }

    {
        entityData *data = new entityData("cubeEnergyCWire", b2Vec2(1, 2));
        data->init = [root, physicalWorld, data](b2Vec2 pos,
        Entity *mainEntity) -> Entity * {
            b2Vec2 nodePos = pos;
            float angle = 0.0f;
            if (mainEntity != nullptr)
            {
                angle = mainEntity->GetAngle() + data->getAngle();
                auto faceEntityData =
                EntityFactory::getEntityData(mainEntity->GetName());
                nodePos = PhysicalWorld::generateNodePos(mainEntity->m_physicalBody,
                        faceEntityData->getSize(),
                        data->getSize());
            }
            b2BodyDef bodyDef = PhysicalWorld::generateBodyDef(nodePos, angle);

            b2PolygonShape polygonShape;
            polygonShape.SetAsBox(data->size.x, data->size.y, b2Vec2(0, 0), 0);
            b2FixtureDef fixtureDef;
            fixtureDef.density = 0.5;
            fixtureDef.friction = 0.2;
            fixtureDef.restitution = 1;
            fixtureDef.shape = &polygonShape;

            auto entity = new CubeEnergyCWire(data->name, root, data->size, pos, 50);
            entity->initPhysical(bodyDef, fixtureDef, physicalWorld.get(),
                                 "CubeEnergyCWireBody", "CubeEnergyCWireFixture");
            return entity;
        };
        EntityFactory::addEntity(data);
    }

    {
        entityData *data = new entityData("Generator", b2Vec2(2, 2));
        data->init = [root, physicalWorld, data](b2Vec2 pos,
        Entity *mainEntity) -> Entity * {
            b2Vec2 nodePos = pos;
            float angle = 0.0f;
            if (mainEntity != nullptr)
            {
                // angle = Math::degreeToRad(data->angle);
                angle = mainEntity->GetAngle() + data->getAngle();
                Log::setLevel(LOG_LEVEL_INFO);
                Log::printLog("angle:%f\n", angle);
                auto faceEntityData =
                EntityFactory::getEntityData(mainEntity->GetName());
                nodePos = PhysicalWorld::generateNodePos(mainEntity->m_physicalBody,
                        faceEntityData->getSize(),
                        data->getSize());
            }
            b2BodyDef bodyDef = PhysicalWorld::generateBodyDef(nodePos, angle);

            b2PolygonShape polygonShape;
            polygonShape.SetAsBox(data->size.x, data->size.y, b2Vec2(0, 0), 0);
            b2FixtureDef fixtureDef =
            PhysicalWorld::generateFixtureDef(&polygonShape);

            auto entity = new Generator(data->name, root, data->size, pos, 30);
            entity->initPhysical(bodyDef, fixtureDef, physicalWorld.get(),
                                 "GeneratorBody", "GeneratorFixture");
            return entity;
        };
        EntityFactory::addEntity(data);
    }

    {
        entityData *data = new entityData("thrusterLittle", b2Vec2(1, 2));
        data->init = [root, physicalWorld, data](b2Vec2 pos,
        Entity *mainEntity) -> Entity * {
            b2Vec2 nodePos = pos;
            float angle = 0.0f;
            if (mainEntity != nullptr)
            {
                // angle = Math::degreeToRad(data->angle);
                angle = mainEntity->GetAngle() + data->getAngle();
                Log::setLevel(LOG_LEVEL_INFO);
                Log::printLog("angle:%f\n", angle);
                auto faceEntityData =
                EntityFactory::getEntityData(mainEntity->GetName());
                nodePos = PhysicalWorld::generateNodePos(mainEntity->m_physicalBody,
                        faceEntityData->getSize(),
                        data->getSize());
            }
            b2BodyDef bodyDef = PhysicalWorld::generateBodyDef(nodePos, angle);

            b2PolygonShape polygonShape;
            polygonShape.SetAsBox(data->size.x, data->size.y, b2Vec2(0, 0), 0);
            b2FixtureDef fixtureDef =
            PhysicalWorld::generateFixtureDef(&polygonShape);

            auto entity = new Thruster(data->name, root, data->size, 100, pos, 45);
            entity->initPhysical(bodyDef, fixtureDef, physicalWorld.get(), "CubeBody",
                                 "CubeFixture");
            return entity;
        };
        EntityFactory::addEntity(data);
    }

    {
        entityData *data = new entityData("gyro", b2Vec2(2, 2));
        data->init = [root, physicalWorld, data](b2Vec2 pos, Entity *mainEntity) -> Entity * {
            b2Vec2 nodePos = pos;
            float angle = 0.0f;
            if (mainEntity != nullptr)
            {
                // angle = Math::degreeToRad(data->angle);
                angle = mainEntity->GetAngle() + data->getAngle();
                Log::setLevel(LOG_LEVEL_INFO);
                Log::printLog("angle:%f\n", angle);
                auto faceEntityData =
                EntityFactory::getEntityData(mainEntity->GetName());
                nodePos = PhysicalWorld::generateNodePos(mainEntity->m_physicalBody,
                        faceEntityData->getSize(),
                        data->getSize());
            }
            b2BodyDef bodyDef = PhysicalWorld::generateBodyDef(nodePos, angle);

            b2PolygonShape polygonShape;
            polygonShape.SetAsBox(data->size.x, data->size.y, b2Vec2(0, 0), 0);
            b2FixtureDef fixtureDef =
            PhysicalWorld::generateFixtureDef(&polygonShape);

            auto entity = new Gyro(data->name, root, data->size, pos, 45);
            entity->initPhysical(bodyDef, fixtureDef, physicalWorld.get(), "GyroBody",
                                 "GyroFixture");
            return entity;
        };
        EntityFactory::addEntity(data);
    }

    {
        entityData *data = new entityData("bullet", b2Vec2(0.2, 0.2));
        data->init = [root, physicalWorld, data](b2Vec2 pos,
        Entity *mainEntity) -> Entity * {
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
    b2Vec2 nodePos = Math::DrawCoordSToPhysicalCoords(
                         sf::Vector2f(windowSize.x / 2, windowSize.y / 2));
    // Gun * gunNode = new Gun(std::string("Gun"), static_cast<GameObject
    // *>(GetRootNode()), physicalWorld.get(), nodePos);
    Person *personNode = new Person(std::string("person"),
                                    static_cast<GameObject *>(GetRootNode()),
                                    physicalWorld.get(), nodePos);
    personNode->init();
    personNode->equip(ItemFactory::generateItem("ArcWelding"));
    // personNode->equip(ItemFactory::generateItem("CuttingMachine"));

    Bag *bag = static_cast<Bag *>(ItemFactory::generateItem(std::string("bag1")));
    for (int i = 0; i < 30; i++) {
        bag->addItem(ItemFactory::generateItem(std::string("bullet1")));
    }
    personNode->wearBag(bag);
    Gun *gun = static_cast<Gun *>(ItemFactory::generateItem(std::string("gun1")));
    // personNode->equip(gun);
    bag->addItem(gun);
    bag->addItem(ItemFactory::generateItem(std::string("CuttingMachine")));
    bag->addItem(ItemFactory::generateItem(std::string("NetConnect")));

    Box *boxNode = static_cast<Box *>(
                       EntityFactory::generateEntity(std::string("box1"), b2Vec2(0, 10)));
    boxNode->SetAngle(0.25 * b2_pi);
    boxNode->addItem(ItemFactory::generateItem(std::string("bullet1")));
    boxNode->addItem(ItemFactory::generateItem(std::string("bullet1")));
    boxNode->addItem(ItemFactory::generateItem(std::string("gun1")));

    auto camera_pos = this->getCamera().get()->getView().getCenter();
    Log::setLevel(LOG_LEVEL_INFO);
    Log::printLog("ViewPos:%f, %f\n", camera_pos.x, camera_pos.y);
    Log::printLog("gunPos:%f, %f\n", personNode->GetPosition().x,
                  personNode->GetPosition().y);
    auto size_view = this->getCamera().get()->getView().getSize();
    Log::printLog("Size:%f, %f\n", size_view.x, size_view.y);
    getCamera().get()->setTrack(personNode, true);

    {
        // b2Vec2 p1(1, 5), p2(3, 3);
        // if (Math::PointInLine(b2Vec2(2, 4), p1, p2)) {
        // Log::printLog("Yes\n");
        // } else {
        // Log::printLog("No\n");
        // }
        b2Vec2 p1(1, 5), p2(3, 3);
        b2Vec2 q1(0, 0), q2(10, 10);
        b2Vec2 result = Math::LinesIntersection(p1, p2, q1, q2);
        Log::printLog("I:%f, %f\n", result.x, result.y);
    }

    // SubscribeEventIml(
    // E_NODEUPDATEEND,
    //[](EventKey key, EventData &data, EventSender *sender) -> void {
    // using namespace slt::NodeUpdateBegin;
    ////b2Vec2 pos = baffleNode->GetPosition();
    //},
    // baffleNode, baffleNode->GetName());

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
            Bullet *bulletNode = nullptr;
            if (resultA != std::string::npos) {
                bulletNode =
                static_cast<Bullet *>(bodyA->GetBody()->GetUserData().data[1]);
            }

            if (resultB != std::string::npos) {
                bulletNode =
                    static_cast<Bullet *>(bodyB->GetBody()->GetUserData().data[1]);
            }
            if (bulletNode != nullptr) {
                bulletNode->setHp(0);
            }
            // GetRootNode()->DeleteChild(bulletNode->GetName());
        }
    });

    Graphic::insertKeyCallBack(sf::Keyboard::Key::Escape, 0,
                               []() -> void { Graphic::Close(); });

    Graphic::insertKeyCallBack(sf::Keyboard::Key::H, 0, [this]() -> void {
        // printf("Move:Left\n");
        this->getCamera().get()->move(-2, 0);
    });
    Graphic::insertKeyCallBack(sf::Keyboard::Key::L, 0, [this]() -> void {
        // printf("Move:Right\n");
        this->getCamera().get()->move(2, 0);
    });
    Graphic::insertKeyCallBack(sf::Keyboard::Key::J, 0, [this]() -> void {
        // printf("Move:Up\n");
        this->getCamera().get()->move(0, 2);
    });
    Graphic::insertKeyCallBack(sf::Keyboard::Key::K, 0, [this]() -> void {
        // printf("Move:Down\n");
        this->getCamera().get()->move(0, -2);
    });
    Graphic::insertKeyCallBack(sf::Keyboard::Key::N, 0, [this]() -> void {
        this->getCamera()->zoom(1.1f);
    });
    Graphic::insertKeyCallBack(sf::Keyboard::Key::B, 0, [this]() -> void {
        this->getCamera()->zoom(1.0f);
    });
    Graphic::insertKeyCallBack(sf::Keyboard::Key::M, 0, [this]() -> void {
        this->getCamera()->zoom(0.9f);
    });
    // Graphic::insertKeyCallBack(sf::Keyboard::Key::G, [this, gunNode]() -> void
    // {
    //     auto pos =
    //     this->GetRootNode()->GetChild(std::string("Gun"))->GetPosition();
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
    Graphic::insertKeyCallBack(sf::Keyboard::Key::C, 0,
                               []() -> void { Log::setDrawUi(); });
    Graphic::insertKeyCallBack(sf::Keyboard::Key::V, 0,
                               []() -> void { Script::setDrawUi(); });
    DEFUN_NONE("hello", []() -> void {
        Log::setLevel(LOG_LEVEL_INFO);
        Log::printLog("print\n");
    })
    cl_object (*_print)(cl_object) = [](cl_object fmt) -> cl_object {
        Log::setLevel(LOG_LEVEL_INFO);
        std::string fmtC = Script::clToString(fmt);
        Log::printLog(fmtC.c_str());
        return ECL_T;
    };
    DEFUN("AddLog", _print, 1);
    cl_object (*generateEntity)(cl_object, int, int) = [](cl_object name, int x,
    int y) -> cl_object {
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

    b2Vec2 pos(0, 0);
    auto personPos = this->GetRootNode()->GetChild("person")->GetPosition();
    auto g = this->GetPhysicalWorld().get()->GetGravity();
    auto text = new sf::Text();
    text->setFont(*ResourceManager::GetFont("yudit"));
    text->setString("G:" + std::to_string(g.x) + "," + std::to_string(g.y) +
                    "\n" + "personPos" + std::to_string(personPos.x) + ", " +
                    std::to_string(personPos.y));
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
    Graphic::getInstance()->DrawPoint(b2Vec2(0, 0), 2MainScene::~MainScene()  */
}
