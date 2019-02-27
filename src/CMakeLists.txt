set(SOURCE_FILES 
    glad.c	
	window.cpp
	shader.cpp
    texture.cpp
	resource_manager.cpp
	sprite_renderer.cpp
    game_object.cpp
    model.cpp
	game.cpp
	main.cpp)

# set variable in parent scope
set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)

add_executable(demo ${SOURCE_FILES})
target_link_libraries(demo ${GLFW_LIBRARIES})
