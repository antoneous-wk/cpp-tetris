cmake_minimum_required(VERSION 3.14)
project(cpp-tetris)

find_package(glfw3 3.2 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(src)
add_subdirectory(test)

target_link_options(demo PRIVATE -Wall -Wextra -ldl)

target_include_directories(demo PRIVATE include)
target_include_directories(demo PRIVATE ${OPENGL_INCLUDE_DIR})
