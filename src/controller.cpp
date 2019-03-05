#include "controller.hpp"

namespace cpp_tetris {

Controller::Controller(GLFWwindow* window) 
  : window_{window} { }  

void Controller::processInput() {
  if(glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window_, true);
}

void Controller::processInput(GameObject& object, float deltaTime) {
  if(glfwGetKey(window_, GLFW_KEY_LEFT) == GLFW_PRESS)
    object.moveX(userInput::LEFT, deltaTime);
  if(glfwGetKey(window_, GLFW_KEY_RIGHT) == GLFW_PRESS)
    object.moveX(userInput::RIGHT, deltaTime);
  if(glfwGetKey(window_, GLFW_KEY_DOWN) == GLFW_PRESS)
    object.moveY(userInput::DOWN, deltaTime);
}

} // namespace cpp_tetris
