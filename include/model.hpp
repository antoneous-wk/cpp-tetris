#ifndef CPP_TETRIS_MODEL_HPP
#define CPP_TETRIS_MODEL_HPP

#include "resource_manager.hpp"
#include "sprite_renderer.hpp"
#include "tetromino.hpp"
#include "controller.hpp"
#include "texture.hpp"
#include <vector>
#include <string>
#include <bitset>
#include <iostream>
#include <random>
#include <ctime>

using std::bitset;
using std::vector;
using std::cout;

enum moveDirection {
  X_DIRECTION,
  Y_DIRECTION
};

// foward declaration
class Game;

namespace cpp_tetris {

class Model {
  friend class Game;
  public:
    Model(ResourceManager& manager);
    ~Model();
    void processInput(Controller& controller, float deltaTime);
    void update(float deltaTime);
    void draw(SpriteRenderer& renderer, float deltaTime);
    private:
    void generateTetromino();
    unsigned generateRandomNumber();
    bool detectCompleteRow();
    void destroyBlocks();
    vector<Tetromino*> tetrominos_;
    ResourceManager& manager_;
};

} // namespace cpp_tetris

#endif // header guard
