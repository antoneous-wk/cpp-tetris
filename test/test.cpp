//include <glad/glad.h>
//include <GLFW/glfw3.h> 
//include "gtest/gtest.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

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

/*
class ModelTest : public ::testing::Test {
  protected:
    ModelTest() {
      game.init();
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      win = game.getWin();
    }
    ~ModelTest() {}
    void SetUp() override {}
    void TearDown() override {}

    cpp_tetris::ResourceManager manager{"./src/demo"};
    cpp_tetris::Game game{manager, 690, 680};
    cpp_tetris::Window* win;
};
*/

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
    cpp_tetris::Game game{manager, 690, 680};
    cpp_tetris::Window* win;
};

TEST_F(TetrominoTest, generateBlockTest) {
  game.model_->generateTetromino();
//  for(cpp_tetris::Tetromino* tetromino : game->model.tetrominos_)
//    tetromino->resolveBlockCoordinates(270);
}

/*
TEST_F(ModelTest, updateTest) {
  float currentTime{0.0f}; 
  float lastTime{0.0f};
  float deltaTime{0.0f};
  // game loop
  while(!glfwWindowShouldClose(win->getWin())) {
    currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    glfwPollEvents();

    game.processInput(); 
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//    game.update(deltaTime);
//    game.render(deltaTime);
    glfwSwapBuffers(win->getWin());
  }
}
*/

/*
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  my_argv = argv; 
  return RUN_ALL_TESTS();
*/
 
} // namespace
