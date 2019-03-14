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
  unsigned number_of_shapes{shape::COUNT-1};
  // create new engine & seed it 
  static default_random_engine e{time(0)};
  // advance internal state without generating #s (this prevents same first #)
  e.discard(10);
  // generate random distribution from 0 to num_of_bricks inclusive
  static uniform_int_distribution<unsigned> u{0, number_of_shapes};
  return u(e);
}

void Model::generateTetromino() {
  tetrominos_.push_back(new Tetromino{generateRandom(),
    manager_.getTexture2D("block")});
}

bool Model::detectCollision(moveDirection direction, const Tetromino& tetromino) {
//  for(unsigned j = 0; j < 3, ++j)
//    tetromino.orientation_[j]
//    tetromino.tetrominoPosition_.x
  
}


void Model::update(Controller& controller, float deltaTime) {
  // generate initial tetromino 
  if(tetrominos_.empty())
    generateTetromino(); 
  // generate another brick if previous brick has been placed or destroyed
  if(!tetrominos_.empty() && (*--tetrominos_.end())->isPlaced_)
    generateTetromino();

  for(Tetromino* tetromino : tetrominos_) {
    tetromino->update(); 
    if(!tetromino->isPlaced_) {
      controller.processInput(*tetromino, deltaTime);
//      if(!detectCollision(moveDirection::Y_DIRECTION, *tetromino))     
        tetromino->moveY(deltaTime);
    }
  }
//    if(tetromino->position_.y >= brick->max_y)  
//      brick->isPlaced_ = true;
}

void Model::draw(SpriteRenderer& renderer, float deltaTime) {
  // run draw method for all tetrominos in tetrominos__ 
  for(Tetromino* tetromino : tetrominos_) 
    tetromino->draw(renderer);
}

// defines a 12 x 17 grid 
// left-most and right-most bits and bottom-most bits equal the value '1'
// remaining bits represent a 10 x 16 grid and equal the value '0'
vector<vector<bitset<12>>> Model::grid = {
  {0x801}, {0x801}, {0x801}, {0x801}, {0x801}, {0x801}, {0x801}, {0x801},
  {0x801}, {0x801}, {0x801}, {0x801}, {0x801}, {0x801}, {0x801}, {0x801},
  {0xFFF}};

} // namespace cpp_tetris
