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

bool Model::detectCollisionY(Tetromino& tetromino) {
  vector<bitset<10>> rows{0, 0, 0, 0};
  unsigned h{0};
  unsigned i{0};
  for(unsigned j = 0; j < 16; ++j) {
    if(j == 0 || j % 4 != 0) {
      rows[i][h] = tetromino.orientation_[j];
      ++h;
    }
    else {
      ++i;
      h = 0;
      rows[i][h] = tetromino.orientation_[j]; 
      ++h;
    }
  }

  for(bitset<10>& bits : rows) {
    if(tetromino.tetrominoPosition_.x <= 6)
      bits <<= (6 - tetromino.tetrominoPosition_.x);
    else
	  bits >>= (tetromino.tetrominoPosition_.x - 6);
  }

  bool isCollision{false};
  unsigned j{tetromino.tetrominoPosition_.y + 4};
  for(unsigned i = 0; i < 4; ++i) {
    if((rows[i] & grid[j]).any()) {
      isCollision = true; 
      if(j >= 1)
        grid[j-1] = grid[j-1] | rows[i];
    }
    if(j >= 1) 
      --j;
  }
  if(isCollision)
    return true;
  else
    return false;
}
 
/*
  unsigned j{tetromino.tetrominoPosition_.y + 4};
  unsigned index{0};
  for(const bitset<10>& bits : rows) {
    if((bits & grid[j]).any()) {
      for(unsigned k = index; k < 4 - index; ++k) 
        grid[--j] = grid[--j] | rows[k];

      //grid[j-1] = grid[j-1] | bits;
      //cout << bits << endl;
      //cout << grid[j] << endl;
      //cout << (bits & grid[j]) << endl << endl;
      return true; 
    }
    //if(j >= 1)
//    ++j;
    ++index;
  }

  return false;
}
*/

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

// defines a 12 x 17 grid 
vector<bitset<10>> Model::grid = 
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x3FF};

} // namespace cpp_tetris
