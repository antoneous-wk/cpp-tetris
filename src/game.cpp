#include "game.hpp"

namespace cpp_tetris {

Game::Game(ResourceManager& manager, int width, int height)
  : state_{GAME_ACTIVE}, keys_{}, width_{width}, height_{height},
    manager_{manager}, win_{nullptr} { }

Game::~Game() {
  if(win_)
    delete win_;
  win_ = nullptr;
}

void Game::init() {
  win_ = new Window{this->width_, this->height_, "CPP-TETRIS"};
}
    

} // namespace cpp_tetris
