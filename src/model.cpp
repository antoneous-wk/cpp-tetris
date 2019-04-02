#include "model.hpp"

namespace cpp_tetris {

Model::Model(ResourceManager& manager)
  : manager_{manager},
    nextTetromino_{nullptr} {}

Model::~Model() {
  for(Tetromino* t : tetrominos_) {
    if(t) {
      delete t;
      t = nullptr;
    }
  }
  if(nextTetromino_)
    delete nextTetromino_; 
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
  static unsigned currentTetromino; 
  static unsigned nextTetromino{generateRandomNumber()};
  currentTetromino = nextTetromino;
  nextTetromino = generateRandomNumber(); 
  tetrominos_.push_back(new Tetromino{getShape(currentTetromino), getColor(currentTetromino),     glm::vec2{3, -4}, manager_.getTexture2D("block")});
  if(nextTetromino_) {
    delete nextTetromino_;
    nextTetromino_ = nullptr;
  }
  if(nextTetromino == tetrominoType::STICK) {
    nextTetromino_ =  new Tetromino{getShape(nextTetromino), getColor(nextTetromino), 
      glm::vec2{13, 1}, manager_.getTexture2D("block")};
  }
  else {
     nextTetromino_ =  new Tetromino{getShape(nextTetromino), getColor(nextTetromino), 
      glm::vec2{13, 2}, manager_.getTexture2D("block")};
  }
}

tetrominoType Model::getShape(unsigned tetromino) {
  switch(tetromino) {
    case(tetrominoType::TEE):
      return tetrominoType::TEE;
    case(tetrominoType::SAW):
      return tetrominoType::SAW;
    case(tetrominoType::ZEE):
      return tetrominoType::ZEE;
    case(tetrominoType::STICK):
      return tetrominoType::STICK;
    case(tetrominoType::RIGHT):
      return tetrominoType::RIGHT;
    case(tetrominoType::LEFT):
      return tetrominoType::LEFT;
    case(tetrominoType::BOX):
      return tetrominoType::BOX;
  }
}

glm::vec3 Model::getColor(unsigned tetromino) {
  switch(tetromino) {
    case(tetrominoType::TEE):
      return {1.0f, 0.3f, 1.0f}; // pink
    case(tetrominoType::SAW):
      return {0.3f, 1.0f, 0.3f}; // green
    case(tetrominoType::ZEE):
      return {1.0f, 0.0f, 0.0f}; // red
    case(tetrominoType::STICK):
      return {0.3f, 1.0f, 1.0f}; // cyan
    case(tetrominoType::RIGHT):
      return {0.0f, 0.0f, 1.0f}; // blue
    case(tetrominoType::LEFT):
      return {1.0f, 0.5f, 0.0f}; // orange
    case(tetrominoType::BOX):
      return {1.0f, 1.0f, 0.3f}; // yellow
  }
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
      // prints the bitwise representation to the console 
      // useful for debugging runtime collision & row destruction logic
      #ifndef NDEBUG
      for(unsigned i = 0; i < 16; ++i) 
        cout << Tetromino::grid[i] << endl;
      cout << endl;
      #endif
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
  nextTetromino_->draw(renderer);
}

} // namespace cpp_tetris
