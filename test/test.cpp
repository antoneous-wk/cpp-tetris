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

//char** my_argv;

class WindowTest : public ::testing::Test {
  protected:
    WindowTest() {}
    ~WindowTest() override {}
    void SetUp() override {}
    void TearDown() override {}

    cpp_tetris::Window myWin{800, 600, "Tetris"};
};

class GameTest : public ::testing::Test {
  protected:
	GameTest() {}
	~GameTest() {}
	void SetUp() override {}
	void TearDown() override {}

    cpp_tetris::ResourceManager resource_manager{"./src/demo"};
    cpp_tetris::Game game{resource_manager, 800, 600};
};

/*
TEST_F(WindowTest, windowInitTest1) {
  ASSERT_EQ(cpp_tetris::Window::isInit, false);
}

TEST_F(WindowTest, windowInitTest2) {
  myWin.init();  
  ASSERT_EQ(cpp_tetris::Window::isInit, true);
}

TEST_F(WindowTest, windowInitTest3) {
  myWin.init();
  myWin.init();
  ASSERT_EQ(cpp_tetris::Window::isInit, true);
}
*/

TEST_F(GameTest, gameInitTest1) {
  ASSERT_EQ(0, game.getWin());
  game.init();
  ASSERT_EQ(true, static_cast<bool>(game.getWin()));	
}

TEST_F(GameTest, gameInitTest2) {
  ASSERT_EQ(0, game.getRenderer());
  game.init();
  ASSERT_EQ(true, static_cast<bool>(game.getRenderer()));
}


/*
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  my_argv = argv; 
  std::cout << "I am here" << std::endl;
  return RUN_ALL_TESTS();
*/
 
} // namespace
