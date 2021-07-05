include_directories(${PROJECT_SOURCE_DIR}/src)
set(MAIN_SRC_LIST Body/GameObject.cpp Body/Bullet/Bullet.cpp Body/Gun/Gun.cpp MainScene/MainScene.cpp StartScene/StartScene.cpp MyApplication.cpp mainTest.cpp)

add_compile_options(-g -Wall)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
add_executable(tank ${MAIN_SRC_LIST})
target_link_libraries(tank slt)
