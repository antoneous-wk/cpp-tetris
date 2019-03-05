#ifndef CPP_TETRIS_MODEL_HPP
#define CPP_TETRIS_MODEL_HPP

#include "resource_manager.hpp"
#include "game_object.hpp"
#include "controller.hpp"
#include "texture.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <ctime>

namespace cpp_tetris {

enum brickType {
  B_LEFT, 
  B_RIGHT,
  B_STICK,
  B_TEE,
  B_ZEE,
  B_SAW,  
  B_BOX,
  NUM_OF_TYPES
};

class Model {
  public:
    Model(ResourceManager& manager);
    ~Model();

    void getInput();
    // iterate through vector and update state of each brick
    void update(Controller& controller, float deltaTime);
    // iterate through vector and draw each brick
    // each brick has a state, will draw based on state
    void draw(SpriteRenderer& renderer, float deltaTime);
  private:
    // generate random brick and append to vector
    void generate();

    std::vector<GameObject*> bricks_;
    ResourceManager& manager_;
};

} // namespace cpp_tetris

#endif // header guard
