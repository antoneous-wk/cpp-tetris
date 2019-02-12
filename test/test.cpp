//include <glad/glad.h>
//include <GLFW/glfw3.h> 
//include "gtest/gtest.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "window.hpp"
#include "resource_manager.hpp"
#include "game_object.hpp"
#include "block.hpp"
#include "game.hpp"

#include "gtest/gtest.h"

namespace {

class WindowTest : public ::testing::Test {
  protected:
    WindowTest() {}
    ~WindowTest() override {}
    void SetUp() override {}
    void TearDown() override {}

  cpp_tetris::Window myWin{800, 600, "Tetris"};
};

TEST_F(WindowTest, isInitFalse) {
  ASSERT_EQ(cpp_tetris::Window::isInit, false);
}

TEST_F(WindowTest, isInitTrue) {
  myWin.init();  
  ASSERT_EQ(cpp_tetris::Window::isInit, true);
}

TEST_F(WindowTest, isInitTrue2) {
  myWin.init();
  myWin.init();
  ASSERT_EQ(cpp_tetris::Window::isInit, true);
}



} // namespace
