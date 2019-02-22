cmake_minimum_required(VERSION 3.12)
project(cpp-tetris)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)
# best practice not to override CMAKE_CXX_FLAGS, only append to it
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -ldl")
set(CMAKE_BUILD_TYPE Debug)

find_package(glfw3 3.2 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(test)

# enable_testing()
# add_test(NAME mytests COMMAND Test)

