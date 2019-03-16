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
vector<bitset<10>> Model::grid =
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x3FF};

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
  unsigned pos{0};
  unsigned row{0};
  // transform tetromino orientation into vector containing four bitset<10>
  // 0100       0000000100  // bits[3]
  // 0100  ---> 0000000100  // bits[2]
  // 1100       0000001100  // bits[1]
  // 0000       0000000000  // bits[0]
  vector<bitset<10>> bits{0, 0, 0, 0};
  for(unsigned b = 0; b < 16; ++b) {
    if(b == 0 || b % 4 != 0) {
      bits[row][pos] = tetromino.orientation_[b];
      ++pos;
    } 
    else {
      ++row;
      pos = 0;
      bits[row][pos] = tetromino.orientation_[b]; 
      ++pos;
    }
  }

  // shift bits in X direction to match current tetronimo X position
  const unsigned offset{bits[0].size() - 4};
  for(bitset<10>& bitRow : bits) {
    if(tetromino.tetrominoPosition_.x <= offset)
      bitRow <<= (offset - tetromino.tetrominoPosition_.x);
    else
	  bitRow >>= (tetromino.tetrominoPosition_.x - offset);
  }

  // detect tetronimo collision in the Y direction
  bool isCollision{false};
  unsigned gridRow{tetromino.tetrominoPosition_.y + 4};
  for(unsigned i = 0; i < 4; ++i) {
    if((bits[i] & grid[gridRow]).any()) {
      isCollision = true; 
      if(gridRow > 0)
        grid[gridRow-1] = grid[gridRow-1] | bits[i];
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
