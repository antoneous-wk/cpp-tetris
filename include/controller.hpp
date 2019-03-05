#ifndef CPP_TETRIS_CONTROLLER_HPP
#define CPP_TETRIS_CONTROLLER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "game_object.hpp"

namespace cpp_tetris {

class Controller {
  public:
    Controller(GLFWwindow* window);

    void processInput();
    void processInput(GameObject& object, float deltaTime); 

  private:
    GLFWwindow* window_;

};

} // namespace cpp_tetris

#endif // header guard
