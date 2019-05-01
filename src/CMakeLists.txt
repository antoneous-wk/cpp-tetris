set(SOURCE_FILES 
    glad.c	
	window.cpp
	shader.cpp
    texture.cpp
	resource_manager.cpp
	sprite_renderer.cpp
    model.cpp
    controller.cpp
    tetromino.cpp
    block.cpp
	game.cpp
	)

# set variable in parent scope
set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)
