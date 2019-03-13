#include "model.hpp"

namespace cpp_tetris {

Model::Model(ResourceManager& manager)
  : manager_{manager} { }

Model::~Model() {
  for(Tetromino* t : tetrominos_) {
    if(t) {
      delete t;
      t = nullptr;
    }
  }
}

unsigned Model::generateRandom() {
  unsigned number_of_bricks{tetrominoType::COUNT-1};
  // create new engine & seed it 
  static default_random_engine e{time(0)};
  // advance internal state without generating #s (this prevents same first #)
  e.discard(10);
  // generate random distribution from 0 to num_of_bricks inclusive
  static uniform_int_distribution<unsigned> u{0, number_of_bricks};
  return u(e);
}

void Model::generateTetromino() {
  tetrominos_.push_back(new Tetromino{generateRandom()});
/*  tetrominos_.push_back(new Tetromino{glm::vec2{140, 0}, size, 
    manager_.getTexture2D(brick_name), color, glm::vec2{500.0f, 60.0f}}); */
}

void Model::update(Controller& controller, float deltaTime) {
/*
  // generate initial brick
  if(bricks_.empty())
    generate(); 
  // generate another brick if previous brick has been placed or destroyed
  if(!bricks_.empty() && (*--bricks_.end())->isPlaced_)
    generate();

  for(GameObject* brick : bricks_) {
    if(brick->position_.y >= brick->max_y)  
      brick->isPlaced_ = true;
    if(!brick->isPlaced_) {
      controller.processInput(*brick, deltaTime);
      brick->moveY(deltaTime);
    }
  }
*/
}

void Model::draw(SpriteRenderer& renderer, float deltaTime) {
  // run draw method for all tetrominos in tetrominos__ 
//  for(Tetromino* tetromino : tetrominos_) 
//    tetromino->draw(renderer);
}

} // namespace cpp_tetris
