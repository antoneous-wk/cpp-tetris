#include "window.hpp"
#include "resource_manager.hpp"
#include "block.hpp"
#include "tetromino.hpp"
#include "controller.hpp"
#include "game.hpp"
#include "model.hpp"
#include "sprite_renderer.hpp"

#include "gtest/gtest.h"

namespace {

class TetrominoTest : public ::testing::Test {
  protected:
    TetrominoTest() {
      game.init();
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      win = game.getWin();
    }
    ~TetrominoTest() {}
    void SetUp() override {}
    void TearDown() override {}

    cpp_tetris::ResourceManager manager{"./src/demo"};
    cpp_tetris::Game game{manager, 730, 680};
    cpp_tetris::Window* win;
};

TEST_F(TetrominoTest, generateBlockTest) {
  float currentTime{0.0f}; 
  float lastTime{0.0f};
  float deltaTime{0.0f};
  // game loop
  while(!glfwWindowShouldClose(win->getWin())) {
    currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    glfwPollEvents();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    game.processInput(deltaTime);
    game.update(deltaTime);
    game.render(deltaTime);
    glfwSwapBuffers(win->getWin());
  }
}

} // namespace
