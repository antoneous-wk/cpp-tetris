#include "controller.hpp"

namespace cpp_tetris {

Controller::Controller(GLFWwindow* window) 
  : window_{window} { }  

void Controller::processInput() {
  if(glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window_, true);
}

void Controller::processInput(Tetromino& tetromino, float deltaTime) {
//  if(glfwGetKey(window_, GLFW_KEY_K) == GLFW_PRESS)
//    tetromino.rotate(deltaTime);
  if(glfwGetKey(window_, GLFW_KEY_LEFT) == GLFW_PRESS)
    tetromino.moveX(userInput::KEY_LEFT, deltaTime);
  if(glfwGetKey(window_, GLFW_KEY_RIGHT) == GLFW_PRESS)
    tetromino.moveX(userInput::KEY_RIGHT, deltaTime);
//  if(glfwGetKey(window_, GLFW_KEY_DOWN) == GLFW_PRESS)
//    tetromino.moveY(userInput::DOWN, deltaTime);
}

} // namespace cpp_tetris
