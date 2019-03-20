#ifndef CPP_TETRIS_CONTROLLER_HPP
#define CPP_TETRIS_CONTROLLER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "tetromino.hpp"

namespace cpp_tetris {

class Controller {
  public:
    Controller(GLFWwindow* window);
    void processInput(Tetromino* tetromino, float deltaTime); 
  private:
    GLFWwindow* window_;
};

} // namespace cpp_tetris

#endif // header guard
