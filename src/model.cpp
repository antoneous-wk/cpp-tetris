#include "model.hpp"

namespace cpp_tetris {

Model::Model(ResourceManager& manager)
  : manager_{manager} {}

Model::~Model() {
  for(Tetromino* t : tetrominos_) {
    if(t) {
      delete t;
      t = nullptr;
    }
  }
}

// defines a 10 x 17 grid of bits
/*
vector<bitset<10>> Model::grid =
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x3FF};
*/

// defines a 12 x 17 grid of bits
// grid consists of 0's bounded by 1's on left, right, bottom 
// note: break line for depiction purposes only 
// 1 0 0 0 0 0 0 0 0 0 0 1
// 1 0 0 0 0 0 0 0 0 0 0 1
// ~~~~~(break line)~~~~~~
// 1 0 0 0 0 0 0 0 0 0 0 1
// 1 0 0 0 0 0 0 0 0 0 0 1
// 1 1 1 1 1 1 1 1 1 1 1 1
vector<bitset<12>> Model::grid =
  {0x801, 0x801, 0x801, 0x801, 0x801, 0x801, 0x801, 0x801,  
   0x801, 0x801, 0x801, 0x801, 0x801, 0x801, 0x801, 0x801, 
   0xFFF};

unsigned Model::generateRandomNumber() {
  unsigned number_of_shapes{shape::COUNT-1};
  // create new engine & seed it 
  static default_random_engine e{time(0)};
  // advance internal state (this prevents same first number)
  e.discard(10);
  // generate random distribution from 0 to num_of_bricks inclusive
  static uniform_int_distribution<unsigned> u{0, number_of_shapes};
  return u(e);
}

void Model::generateTetromino() {
  tetrominos_.push_back(new Tetromino{generateRandomNumber(),
    manager_.getTexture2D("block")});
}

bool Model::detectCollisionY(Tetromino& tetromino) {
  // detect tetronimo collision in the Y direction and update grid
  bool isCollision{false};
  unsigned gridRow{tetromino.tetrominoPosition_.y + 4};
  for(unsigned i = 0; i < 4; ++i) {
    if((tetromino.bits_[i] & grid[gridRow]).any()) {
      isCollision = true; 
      if(gridRow > 0)
        grid[gridRow-1] = grid[gridRow-1] | tetromino.bits_[i];
    }
    if(gridRow > 0) 
      --gridRow;
  }
  return isCollision;
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
        if(!detectCollisionY(*tetromino))     
          tetromino->moveY(deltaTime);
        else
          tetromino->isPlaced_ = true;
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

} // namespace cpp_tetris
