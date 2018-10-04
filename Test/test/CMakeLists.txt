include_directories(${PROJECT_SOURCE_DIR}/src)
set(MAIN_SRC_LIST BreakoutScene/MyBreakoutScene.cpp MyApplication.cpp mainTest.cpp)

add_compile_options(-g -Wall)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
add_executable(main ${MAIN_SRC_LIST})
target_link_libraries(main slt)
