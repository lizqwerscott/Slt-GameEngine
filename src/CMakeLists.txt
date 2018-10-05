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
				  	Graphic/Graphic.cpp 
				  	Math/Tree.h
				  	Scene/SNode.cpp 
				  	Scene/Scene.cpp 
				  	Scene/SceneManager.cpp 
				  	Engine/Engine.cpp
				  	Application.cpp )

add_compile_options(-g -Wall)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
add_library(slt ${Header_SRC_LIST} ${Tool_SRC_LIST})
set_target_properties(slt PROPERTIES OUTPUT_NAME "slt")
target_link_libraries(slt -lsfml-graphics -lsfml-window -lsfml-system dl Box2D)
