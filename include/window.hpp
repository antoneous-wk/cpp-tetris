#ifndef CPP_TETRIS_WINDOW_HPP
#define CPP_TETRIS_WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>

namespace cpp_tetris
{

// forward declarations
void framebuffer_size_callback(GLFWwindow* win, int width, int height);

static bool isInit{false};

void Init()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  isInit = true;
}

class Window 
{
  public:
    Window(unsigned, unsigned, const char*); 
    ~Window();

    inline GLFWwindow* getWin() const { return win_; }
	
  private:
    GLFWwindow* win_;
    unsigned width_;
    unsigned height_;
    const char* title_;
};

Window::Window(unsigned width, unsigned height, const char* title)
    : win_{nullptr}, width_{width}, height_{height}, title_{title}
{
  if(isInit)
  // create window and its associated OpenGL context
    win_ = glfwCreateWindow(width_, height_, title_, nullptr, nullptr);
  else
	throw std::runtime_error("Must initialize GLFW before creating window");
  if (!win_)
	throw std::runtime_error("Failed to create GLFW window");

  glfwMakeContextCurrent(win_);
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
  }
  glViewport(0, 0, width_, height_);
  // register callback function to be called by GLFW when window is resized
  glfwSetFramebufferSizeCallback(win_, framebuffer_size_callback);
}

Window::~Window()
{
  glfwTerminate();
  win_ = nullptr;
}
	
inline void framebuffer_size_callback(GLFWwindow* win, int width, int height)
{
  glViewport(0,0, width, height);
}

inline void process_input(GLFWwindow* win)
{
  if(glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(win, true);
}

} // namespace cpp_tetris

#endif // header guard
