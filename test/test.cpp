//include <glad/glad.h>
//include <GLFW/glfw3.h> 
//include "gtest/gtest.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "window.hpp"
#include "resource_manager.hpp"
#include "game.hpp"
#include "sprite_renderer.hpp"

#include "gtest/gtest.h"

namespace {

class GameTest : public ::testing::Test {
  protected:
	GameTest() {}
	~GameTest() {}
	void SetUp() override {}
	void TearDown() override {}

    cpp_tetris::ResourceManager resource_manager{"./src/demo"};
    cpp_tetris::Game game{resource_manager, 620, 600};
};

TEST_F(GameTest, gameInitTest) {
  ASSERT_EQ(0, game.getWin());
  ASSERT_EQ(0, game.getRenderer());
  game.init();
  ASSERT_EQ(true, static_cast<bool>(game.getWin()));	
  ASSERT_EQ(true, static_cast<bool>(game.getRenderer()));
}

TEST_F(GameTest, renderTest) {
  game.init();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  cpp_tetris::Window* win{game.getWin()};
  // game loop
  while(!glfwWindowShouldClose(win->getWin())) {
    cpp_tetris::process_input(win->getWin());
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    game.render(0.0f);
    glfwSwapBuffers(win->getWin());
    glfwPollEvents();
  }
}

/*
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  my_argv = argv; 
  std::cout << "I am here" << std::endl;
  return RUN_ALL_TESTS();
*/
 
} // namespace
