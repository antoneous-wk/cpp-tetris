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

void Model::processInput(Controller& controller, float deltaTime) {
    // process input for the last (newest) tetromino in the vector
    Tetromino*& tetromino{*--tetrominos_.end()}; 
    if(!tetrominos_.empty() && !(tetromino->isPlaced_)) {
      controller.processInput(tetromino, deltaTime);
      if(tetromino->detectCollisionY())
        tetromino->isPlaced_ = true;
      else
        tetromino->moveY(deltaTime);
    }
}

void Model::update(float deltaTime) {
  // generate initial tetromino 
  if(tetrominos_.empty())
    generateTetromino(); 
  // generate another tetromino if previous tetromino has been placed
  if(!tetrominos_.empty() && (*--tetrominos_.end())->isPlaced_)
    generateTetromino();
  // update
  for(Tetromino* tetromino : tetrominos_) 
    if(!tetromino->isPlaced_) 
      tetromino->update();
}

/*
bool Model::detectCompleteRow() {
  for(unsigned i = Tetromino::grid.size()-2; i >= 0; --i) {
    if(Tetromino::grid[i].all())
      return true;
  }
  return false;
}

void Model::destroyBlocks() {
  for(Tetromino* tetromino : tetrominos_)
    if(tetromino->isPlaced_)
      tetromino->destroyBlocks();
}
*/

void Model::draw(SpriteRenderer& renderer, float deltaTime) {
  for(Tetromino* tetromino : tetrominos_) 
    tetromino->draw(renderer);
}

} // namespace cpp_tetris
