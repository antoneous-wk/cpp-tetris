set(SOURCE_FILES 
	main.cpp
	shader.cpp
	glad.c)

# set variable in parent scope
set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)

add_executable(demo ${SOURCE_FILES})
target_link_libraries(demo ${GLFW_LIBRARIES})
