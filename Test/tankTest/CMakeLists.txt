include_directories(${PROJECT_SOURCE_DIR}/src)
set(MAIN_SRC_LIST 
    Body/GameObject.cpp 

    Body/BoxBase.cpp

    Body/Entity/Box/Box.cpp
    Body/Entity/Entity.cpp
    Body/Entity/Bullet/Bullet.cpp 
    Body/Entity/Biological/Biological.cpp
    Body/Entity/Biological/Person.cpp

    Body/Item/Bag/Bag.cpp
    Body/Item/Gun/BulletI.cpp
    Body/Item/Gun/Gun.cpp

    MainScene/MainScene.cpp 
    StartScene/StartScene.cpp 
    MyApplication.cpp 
    mainTest.cpp)

add_compile_options(-g -Wall)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
add_executable(tank ${MAIN_SRC_LIST})
target_link_libraries(tank slt)
