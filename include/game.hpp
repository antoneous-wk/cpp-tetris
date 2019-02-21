#ifndef CPP_TETRIS_GAME_HPP
#define CPP_TETRIS_GAME_HPP

#include "resource_manager.hpp"
#include "window.hpp"

namespace cpp_tetris {

enum gameState {
  GAME_ACTIVE,
  GAME_MENU,
  GAME_WIN,
};

class Game {
  public:
    Game(ResourceManager& manager, int width, int height);
    ~Game();

    void init();
    void processInput();
    void update(float delta_time);
    void render(float delta_time);

	Window* getWin() const { return win_; } 	

  private:
    gameState state_;
    bool keys_[1024];
    int width_, height_ ;
    const ResourceManager& manager_;
    Window* win_;
};

} // namespace cpp_tetris

#endif // header guard
