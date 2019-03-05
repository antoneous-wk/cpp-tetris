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
#include "controller.hpp"
#include "game.hpp"
#include "model.hpp"
#include "sprite_renderer.hpp"

#include "gtest/gtest.h"

namespace {

//old test fixtures
/*
class GameTest : public ::testing::Test {
  protected:
	GameTest() {}
	~GameTest() {}
	void SetUp() override {}
	void TearDown() override {}

    cpp_tetris::ResourceManager resource_manager{"./src/demo"};
    cpp_tetris::Game game{resource_manager, 690, 600};
};
*/
/*
class GameObjectTest : public ::testing::Test {
  protected:
    GameObjectTest() : brick{nullptr} {
      game.init();
      brick = new cpp_tetris::GameObject{manager.getTexture2D("saw")};
    } 
    ~GameObjectTest() {
      if(brick) delete brick;
      brick = nullptr;
    }
    void SetUp() override {}
    void TearDown() override {}

   cpp_tetris::ResourceManager manager{"./src/demo"};
   cpp_tetris::Game game{manager, 690, 600};
   cpp_tetris::GameObject* brick;
};
*/

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
    cpp_tetris::Game game{manager, 690, 600};
    cpp_tetris::Window* win;
};

// old tests   
/*
TEST_F(GameTest, gameInitTest) {
  ASSERT_EQ(0, game.getWin());
  ASSERT_EQ(0, game.getRenderer());
  game.init();
  ASSERT_EQ(true, static_cast<bool>(game.getWin()));	
  ASSERT_EQ(true, static_cast<bool>(game.getRenderer()));
}
/*
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
*/
/*
TEST_F(GameObjectTest, drawTest) {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  cpp_tetris::Window* win{game.getWin()};
  // game loop
  while(!glfwWindowShouldClose(win->getWin())) {
    cpp_tetris::process_input(win->getWin());
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    game.render(0.0f);

    // we are testing this line
    brick->draw(game.getRenderer());

    glfwSwapBuffers(win->getWin());
    glfwPollEvents();
  }
}
*/
/*
TEST_F(ModelTest, drawTest) {
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
*/

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
    game.update(deltaTime);
    game.render(deltaTime);
    glfwSwapBuffers(win->getWin());
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
