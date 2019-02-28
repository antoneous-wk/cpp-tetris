#ifndef CPP_TETRIS_MODEL_HPP
#define CPP_TETRIS_MODEL_HPP

#include "resource_manager.hpp"
#include "game_object.hpp"
#include "texture.hpp"
#include <vector>

#include <iostream>

namespace cpp_tetris {

//class GameObject;

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
    Model(ResourceManager& manager);
    ~Model();

    // iterate through vector and update state of each brick
    void update();

    // iterate through vector and draw each brick
    // each brick has a state, will draw based on state
    void draw(SpriteRenderer& renderer);

  private:
    // generate random brick and append to vector
    void generate();

    std::vector<GameObject*> bricks_;
    ResourceManager& manager_;
};

} // namespace cpp_tetris

#endif // header guard
