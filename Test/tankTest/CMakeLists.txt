include_directories(${PROJECT_SOURCE_DIR}/src)
set(MAIN_SRC_LIST 
    Body/GameObject.cpp 

    Body/ContainerBase.cpp
    Body/ItemTManager.cpp
    Body/BoxBase.cpp
    Body/ToolBox.cpp

    Body/Entity/Box/Box.cpp
    Body/Entity/Entity.cpp
    Body/Entity/Bullet/Bullet.cpp 
    Body/Entity/Biological/Biological.cpp
    Body/Entity/Biological/Person.cpp
    Body/Entity/Cube/Cube.cpp
    Body/Entity/Thruster/Thruster.cpp
    Body/Entity/Computer/Computer.cpp
    Body/Entity/Seat/Seat.cpp
    Body/Entity/EntityFactory.cpp

    Body/Item/Bag/Bag.cpp
    Body/Item/Consume/BulletI/BulletI.cpp
    Body/Item/Weapon/Gun/Gun.cpp
    Body/Item/Tool/ArcWelding/ArcWelding.cpp
    Body/Item/Tool/CuttingMachine/CuttingMachine.cpp
    Body/Item/Tool/NetConnect/NetConnect.cpp
    Body/Item/ItemFactory.cpp

    MainScene/MainScene.cpp 
    StartScene/StartScene.cpp 
    MyApplication.cpp 
    mainTest.cpp)

add_compile_options(-g -Wall)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
add_executable(tank ${MAIN_SRC_LIST})
target_link_libraries(tank slt)
