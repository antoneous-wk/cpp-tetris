#ifndef CPP_TETRIS_GAME_HPP
#define CPP_TETRIS_GAME_HPP

namespace cpp_tetris {

enum gameState {
  GAME_ACTIVE,
  GAME_MENU,
  GAME_WIN,
};

class Game {
  public:
    Game(int width, int height) 
      : state_{GAME_ACTIVE}, keys_{}, width_{width}, height_{height} { }
    ~Game();

    void init();
    void processInput();
    void update(float delta_time);
    void render(float delta_time);

  private:
    gameState state_;
    bool keys_[1024];
    int width_, height_ ;
};

} // namespace cpp_tetris

#endif // header guard
