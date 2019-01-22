set(SOURCE_FILES main.cpp PARENT_SCOPE)

add_executable(demo main.cpp glad.c)
target_link_libraries(demo ${GLFW_LIBRARIES})
