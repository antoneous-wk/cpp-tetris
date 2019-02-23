#include "window.hpp"

namespace cpp_tetris {

// static members
bool Window::isInit{false};

Window::Window(unsigned width, unsigned height, const char* title)
  : win_{nullptr}, width_{width}, height_{height}, title_{title} { }

Window:: ~Window() {
  glfwTerminate();
  win_ = nullptr;
  isInit = false;
}

void Window::init() {
  if(isInit == false) {  
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window and its associated OpenGL context
    win_ = glfwCreateWindow(width_, height_, title_, nullptr, nullptr);
    if(!win_)
      throw std::runtime_error("Failed to create GLFW window");
    glfwMakeContextCurrent(win_);
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) 
      throw std::runtime_error("Failed to initialize GLAD");
    
    glViewport(0, 0, width_, height_);
    // register callback function to be called by GLFW when window is resized
    glfwSetFramebufferSizeCallback(win_, framebuffer_size_callback);
  }
  isInit = true;
}

void framebuffer_size_callback(GLFWwindow* win, int width, int height) {
  glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* win) {
  if(glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(win, true);
}

} // namespace cpp_tetris
