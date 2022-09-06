set(Header_SRC_LIST Math/Math.cpp)
set(Memory_SRC_LIST MemoryManager/Ref.cpp
				  	MemoryManager/AutoreleasePool.cpp
				  	MemoryManager/PoolManager.cpp )
set(Event_SRC_LIST  Event/EventSender.cpp
					Event/EventReciver.cpp
					Event/EventHandler.cpp
					Event/EventHandlerIml.cpp
					Event/EventManager.cpp)
set(Tool_SRC_LIST 	${Memory_SRC_LIST}
					${Event_SRC_LIST}
					Object.cpp
				  	ResourceManager/ResourceManager.cpp
				  	Physical/PhysicalFixture.cpp
				  	Physical/PhysicalBody.cpp
				  	Physical/PhysicalWorld.cpp

                    Graphic/UI/imgui.cpp
                    Graphic/UI/imgui_draw.cpp
                    Graphic/UI/imgui_widgets.cpp
                    Graphic/UI/imgui-SFML.cpp
                    Graphic/UI/imgui_tables.cpp
                    Graphic/UI/imgui_demo.cpp

                    Graphic/Camera.cpp
				  	Graphic/Graphic.cpp
                    Log/Log.cpp
                    Script/Script.cpp
				  	Math/Tree.h
				  	Scene/SNode.cpp
				  	Scene/Scene.cpp
				  	Scene/SceneManager.cpp
				  	Engine/Engine.cpp
				  	Application.cpp )

include_directories(${PROJECT_SOURCE_DIR}/include)

add_compile_options(-g -Wall -std=c++11)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
add_library(slt ${Header_SRC_LIST} ${Tool_SRC_LIST})
set_target_properties(slt PROPERTIES OUTPUT_NAME "slt")
target_link_libraries(slt -lsfml-graphics -lsfml-window -lsfml-system -lGL dl box2d)
