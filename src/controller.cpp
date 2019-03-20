#include "controller.hpp"

namespace cpp_tetris {

Controller::Controller(GLFWwindow* window) 
  : window_{window} { }  

void Controller::processInput(Tetromino* tetromino, float deltaTime) {
  static int keyUpOldState{GLFW_RELEASE};
//  static int keyDownOldState{GLFW_RELEASE};
  static int keyLeftOldState{GLFW_RELEASE};
  static int keyRightOldState{GLFW_RELEASE};

  int keyUpNewState{glfwGetKey(window_, GLFW_KEY_UP)};
//  int keyDownNewState{glfwGetKey(window_, GLFW_KEY_DOWN)};
  int keyLeftNewState{glfwGetKey(window_, GLFW_KEY_LEFT)};
  int keyRightNewState{glfwGetKey(window_, GLFW_KEY_RIGHT)};

  if(keyUpNewState == GLFW_PRESS && keyUpOldState == GLFW_RELEASE) 
    tetromino->rotate(deltaTime);
  if(keyLeftNewState == GLFW_PRESS && keyLeftOldState == GLFW_RELEASE)
    tetromino->moveX(userInput::KEY_LEFT, deltaTime);
  if(keyRightNewState == GLFW_PRESS && keyRightOldState == GLFW_RELEASE)
    tetromino->moveX(userInput::KEY_RIGHT, deltaTime);

  keyUpOldState = keyUpNewState;
  keyLeftOldState = keyLeftNewState;
  keyRightOldState = keyRightNewState;
}

} // namespace cpp_tetris
