#ifndef CPP_TETRIS_MODEL_HPP
#define CPP_TETRIS_MODEL_HPP

#include "game_object.hpp"
#include <vector>

namespace cpp_tetris {

enum brickType {
  B_LEFT, 
  B_RIGHT,
  B_STICK,
  B_TEE,
  B_ZEE,
  B_SAW,  
};

class Model {
  public:
    Model();
    ~Model();

    // random brick generation 
    // generate brick and append to bricks_ vector
    void generate();

    // iterate through bricks_ and draw each brick
    // each brick has a state
    void draw(SpriteRenderer& renderer);

  private:
//    std::vector<GameObject*> bricks_;
};

} // namespace cpp_tetris

#endif // header guard
