#ifndef CPP_TETRIS_GAME_HPP
#define CPP_TETRIS_GAME_HPP

#include "resource_manager.hpp"
#include "window.hpp"
#include "sprite_renderer.hpp"

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
    SpriteRenderer* getRenderer() const { return renderer_; }
    

  private:
    gameState state_;
    bool keys_[1024];
    int width_, height_ ;
    Window* win_;
    SpriteRenderer* renderer_;
    ResourceManager& manager_;

};

} // namespace cpp_tetris

#endif // header guard
