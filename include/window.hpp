#ifndef CPP_TETRIS_WINDOW_HPP
#define CPP_TETRIS_WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>

namespace cpp_tetris {

class Window {
  public:
    Window(unsigned width, unsigned height, const char* title);
    ~Window(); 

    void init();
    GLFWwindow* getWin() const { return win_; }
    static bool isInit;

  private:
    GLFWwindow* win_;
    unsigned width_;
    unsigned height_;
    const char* title_;
};

} // namespace cpp_tetris

#endif // header guard
