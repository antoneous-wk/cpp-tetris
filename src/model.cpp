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
  unsigned number_of_shapes{tetrominoType::COUNT-1};
  // create new engine & seed it 
  static default_random_engine e{time(0)};
  // advance internal state (this prevents same first number)
  e.discard(10);
  // generate random distribution from 0 to num_of_bricks inclusive
  static uniform_int_distribution<unsigned> u{0, number_of_shapes};
  return u(e);
/*
  static unsigned index;
  if(index == 5)
    index = 0;
  vector<unsigned> shape{5, 0, 3, 6, 3};
  return shape[index++]; 
*/
}

void Model::generateTetromino() {
  tetrominoType shape;
  glm::vec3 color;
  switch(generateRandomNumber()) {
    case(tetrominoType::TEE):
      color = {1.0f, 0.3f, 1.0f}; // pink
      shape = tetrominoType::TEE;
      break;
    case(tetrominoType::SAW):
      color = {0.3f, 1.0f, 0.3f}; // green
      shape = tetrominoType::SAW;
      break;
    case(tetrominoType::ZEE):
      color = {1.0f, 0.0f, 0.0f}; // red
      shape = tetrominoType::ZEE;
      break;
    case(tetrominoType::STICK):
      color = {0.3f, 1.0f, 1.0f}; // cyan
      shape = tetrominoType::STICK;
      break;
    case(tetrominoType::RIGHT):
      color = {0.0f, 0.0f, 1.0f}; // blue
      shape = tetrominoType::RIGHT;
      break;
    case(tetrominoType::LEFT):
      color = {1.0f, 0.5f, 0.0f}; // orange
      shape = tetrominoType::LEFT;
      break;
    case(tetrominoType::BOX):
      color = {1.0f, 1.0f, 0.3f}; // yellow
      shape = tetrominoType::BOX;
      break;
  }
  tetrominos_.push_back(new Tetromino{shape, color, manager_.getTexture2D("block")});
}

void Model::processInput(Controller& controller, float deltaTime) {
  // implement delay to slide tetromino after placement    
  static float timeSinceCollisionY{0.0f};
  static bool slideDelay{false};
  if(slideDelay)
    timeSinceCollisionY += deltaTime;
  // process input for the last (most current) tetromino
  Tetromino*& tetromino{*--tetrominos_.end()}; 
  if(!tetrominos_.empty() && !(tetromino->isPlaced_)) {
    controller.processInput(tetromino, deltaTime);
    // pass argument 'false' to detectCollisionY() to prevent updating grid
    if(!slideDelay && tetromino->detectCollisionY(false)) {
      timeSinceCollisionY = 0.0f;
      slideDelay = true;
    }
    if(slideDelay && timeSinceCollisionY > 0.150f && tetromino->detectCollisionY()) {
      tetromino->isPlaced_ = true;
      slideDelay = false;

      for(unsigned i = 0; i < 16; ++i) 
        cout << Tetromino::grid[i] << endl;
      cout << endl;
    }
    if(!slideDelay && !tetromino->detectCollisionY(false)) 
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
  // detect and destroy any complete rows
  if(detectCompleteRows()) 
    destroyCompleteRows();
}

bool Model::detectCompleteRows() {
  completeRows_.clear();
  bool isCompleteRow{false};
  for(unsigned i = 0; i < 16; ++i) {
    if(Tetromino::grid[i].all()) {
       isCompleteRow = true; 
       completeRows_.push_back(i);
    }
  } 
  return isCompleteRow;
}

void Model::destroyCompleteRows() {
  for(Tetromino* tetromino : tetrominos_) {
    if(tetromino->isPlaced_)
      tetromino->destroyBlocks(completeRows_);
  }
}

void Model::draw(SpriteRenderer& renderer, float deltaTime) {
  for(Tetromino* tetromino : tetrominos_) 
    tetromino->draw(renderer);
}

} // namespace cpp_tetris
