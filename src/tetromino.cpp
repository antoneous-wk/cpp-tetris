#include "tetromino.hpp"

namespace cpp_tetris {

Tetromino::Tetromino(unsigned tetromino, Texture2D& sprite)
  : isPlaced_{false},
    velocity_{800, 100} {
  setAttributes(tetromino);
  // resolve block coordinates at 0 deg orientation
  resolveRelativePosition(0);    
  resolveAbsolutePosition();
  generateBlocks(sprite);
}

Tetromino::~Tetromino() {
  for(Block* b : blocks_) {
    if(b) {
      delete b;
      b = nullptr;
    }
  }
}

void Tetromino::draw(SpriteRenderer& renderer) {
  for(Block* block : blocks_)  
    block->draw(renderer);
}

void Tetromino::moveX(userInput input, float deltaTime) {
  static float dx{0.0f};
  dx += velocity_.x * deltaTime;
  if(dx >= grid::SPACING) {
    int deltaX; 
    switch(input) {
      case(userInput::KEY_LEFT): {
        deltaX = -1;
        break;
      }
      case(userInput::KEY_RIGHT): {
        deltaX = 1;
        break;
      }
    }    
       tetrominoPosition_.x += deltaX;
    for(Block* block : blocks_)
      block->moveX(deltaX * grid::SPACING);
    dx = 0.0f;
  }
}

void Tetromino::moveY(float deltaTime) {
  static float dy{0.0f};
  dy += velocity_.y * deltaTime;
  if(dy >= grid::SPACING) {
    unsigned deltaY{1};
    tetrominoPosition_.y += deltaY;
    for(Block* block : blocks_)
      block->moveY(deltaY * grid::SPACING);
    dy = 0.0f;
  }
}

void Tetromino::setAttributes(unsigned tetromino) {
  // set starting position for tetromino
  tetrominoPosition_ = {2, 0};
  tetromino_ = tetrominos[tetromino];
  switch(tetromino) {
    case(shape::LEFT):
      color_ = {1.0f, 0.5f, 0.0f}; // orange
      break;
    case(shape::RIGHT):
      color_ = {0.0f, 0.0f, 1.0f}; // blue
      break;
    case(shape::STICK):
      color_ = {0.3f, 1.0f, 1.0f}; // cyan
      break;
    case(shape::TEE):
      color_ = {1.0f, 0.3f, 1.0f}; // pink
      break;
    case(shape::ZEE):
      color_ = {1.0f, 0.0f, 0.0f}; // red
      break;
    case(shape::SAW):
      color_ = {0.3f, 1.0f, 0.3f}; // green
      break;
    case(shape::BOX):
      color_ = {1.0f, 1.0f, 0.3f}; // yellow
      break;
  }
}

// resolve relative position (in grid coordinates) for each block
// coordinates are relative to top left coordinate of 4 x 4 tetromino grid
// order of coordinates is x1, y1, x2, y2, x3, y3, x4, y4 
void Tetromino::resolveRelativePosition(unsigned orientation) {
  unsigned index;
  switch(orientation) {
    case(0): index = 0; break;
    case(90): index = 1; break;
    case(180): index = 2; break;     
    case(270): index = 3; break;
  }
  // resolve relative coordinates
  for(int j = 15; j >= 0; --j) {
    if(tetromino_[index][j] == 1) {
      // resolve relative x (column) coordinate for each block
      if(j == 15 || j == 11 || j == 7 || j == 3) 
        blockPosition_.push_back(0); 
      else if(j % 2 == 0 && j % 4 != 0) 
        blockPosition_.push_back(1); 
      else if(j % 4 == 0) 
        blockPosition_.push_back(3); 
      else 
        blockPosition_.push_back(2); 
      // resolve relative y (row) coordinate for each block
      if(j >= 12) 
        blockPosition_.push_back(0); 
      else if(j >= 8) 
        blockPosition_.push_back(1); 
      else if(j >= 4) 
        blockPosition_.push_back(2); 
      else 
        blockPosition_.push_back(3); 
   } 
  }
}

// resolve absolute position (in pixels) for each block
void Tetromino::resolveAbsolutePosition() {
  for(unsigned j = 0; j < 7; j+=2) {
    blockPosition_[j] += tetrominoPosition_.x;
    blockPosition_[j] = blockPosition_[j] * grid::SPACING + grid::X_OFFSET;
    blockPosition_[j+1] += tetrominoPosition_.y;
    blockPosition_[j+1] = blockPosition_[j+1] * grid::SPACING + grid::Y_OFFSET; 
  }
} 

void Tetromino::generateBlocks(Texture2D& sprite) {
  for(unsigned j = 0; j < 7; j+=2) {
    blocks_.push_back(new Block{glm::vec2{blockPosition_[j],
      blockPosition_[j+1]}, sprite, color_});
  }
}

// each 16 bit hex number represents a tetromino orientation in 4x4 grid
// there are four blocks per tetromino grid, example:
// 0 1 0 0
// 1 1 0 0
// 0 1 0 0
// 0 0 0 0
vector<vector<bitset<16>>> Tetromino::tetrominos =
    // 0    // 90   // 180  // 270
  {{0x4640, 0x0E40, 0x4C40, 0x4E00},     // 'tee'
   {0x8C40, 0x6C00, 0x8C40, 0x6C00},     // 'saw'
   {0x4C80, 0xC600, 0x4C80, 0xC600},     // 'zee'
   {0x4444, 0x0F00, 0x4444, 0x0F00},     // 'stick'
   {0x44C0, 0x8E00, 0xC880, 0xE200},     // 'right'
   {0x88C0, 0xE800, 0xC440, 0x2E00},     // 'left'
   {0xCC00, 0xCC00, 0xCC00, 0xCC00}};    // 'box'





}  // namespace cpp_tetris
