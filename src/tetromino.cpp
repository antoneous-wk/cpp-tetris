#include "tetromino.hpp"

namespace cpp_tetris {

Tetromino::Tetromino(unsigned tetromino, Texture2D& sprite)
  : tetromino_{tetrominos[tetromino]},
    tetrominoPosition_{3, -4},
    color_{setColor(tetromino)},
    isPlaced_{false},
    velocity_{0, 100}, 
    angle_{0} {
  
  setOrientation(0);  
  update();
  generateBlocks(sprite);
}

Tetromino::~Tetromino() {
  for(Block* b : blocks_) {
    if(b) delete b;
    b = nullptr;
  }
}

void Tetromino::update() {
  resolveRelativePosition();
  resolveAbsolutePosition();
  updateBits();
}

// Tetromino::updateBits() //
/*
void Tetromino::updateBits() {
  unsigned pos{0};
  unsigned row{0};
  // transform tetromino orientation into vector containing four bitset<10>
  // 0100       0000000100  // bits_[3]
  // 0100  ---> 0000000100  // bits_[2]
  // 1100       0000001100  // bits_[1]
  // 0000       0000000000  // bits_[0]
  bits_ = {0, 0, 0, 0};
  for(unsigned b = 0; b < 16; ++b) {
    if(b == 0 || b % 4 != 0) {
      bits_[row][pos] = orientation_[b];
      ++pos;
    }
    else {
      ++row;
      pos = 0;
      bits_[row][pos] = orientation_[b];
      ++pos;
    }
  } 
  // shift bits in X direction to match current X position
  const unsigned offset{bits_[0].size() - 4};
  for(bitset<10>& bitRow : bits_) {
    if(tetrominoPosition_.x <= offset)
      bitRow <<= (offset - tetrominoPosition_.x);
    else
      bitRow >>= (tetrominoPosition_.x - offset);
  }
}
*/

void Tetromino::updateBits() {
  unsigned pos{0};
  unsigned row{0};
  // transform tetromino orientation into vector containing four bitset<12>
  // 0100       000000000100  // bits_[3]
  // 0100  ---> 000000000100  // bits_[2]
  // 1100       000000001100  // bits_[1]
  // 0000       000000000000  // bits_[0]
  bits_ = {0, 0, 0, 0};
  for(unsigned b = 0; b < 16; ++b) {
    if(b == 0 || b % 4 != 0) {
      bits_[row][pos] = orientation_[b];
      ++pos;
    }
    else {
      ++row;
      pos = 0;
      bits_[row][pos] = orientation_[b];
      ++pos;
    }
  } 
  // shift bits in X direction to match current X position
  const unsigned offset{bits_[0].size() - 5};
  for(bitset<12>& bitRow : bits_) {
    if(tetrominoPosition_.x <= offset)
      bitRow <<= (offset - tetrominoPosition_.x);
    else
      bitRow >>= (tetrominoPosition_.x - offset);
  }
}

void Tetromino::draw(SpriteRenderer& renderer) {
  unsigned j = 0; 
  for(Block* block : blocks_) {
    block->draw(renderer, glm::vec2(blockPosition_[j], blockPosition_[j+1]));
    j+=2;
  }
}

void Tetromino::rotate(float deltaTime) {
  if(angle_ == 270) 
    angle_ = 0;
  else 
    angle_ += 90;
  setOrientation(angle_);
}

void Tetromino::moveX(userInput input, float deltaTime) {
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

glm::vec3 Tetromino::setColor(unsigned tetromino) {
  glm::vec3 color;
  switch(tetromino) {
    case(shape::LEFT):
      color = {1.0f, 0.5f, 0.0f}; // orange
      break;
    case(shape::RIGHT):
      color = {0.0f, 0.0f, 1.0f}; // blue
      break;
    case(shape::STICK):
      color = {0.3f, 1.0f, 1.0f}; // cyan
      break;
    case(shape::TEE):
      color = {1.0f, 0.3f, 1.0f}; // pink
      break;
    case(shape::ZEE):
      color = {1.0f, 0.0f, 0.0f}; // red
      break;
    case(shape::SAW):
      color = {0.3f, 1.0f, 0.3f}; // green
      break;
    case(shape::BOX):
      color = {1.0f, 1.0f, 0.3f}; // yellow
      break;
  }
  return color;
}

void Tetromino::setOrientation(unsigned angle) {
  angle_ = angle;
  switch(angle_) {
    case(0): 
      orientation_ = tetromino_[0]; 
      break;
    case(90): 
      orientation_ = tetromino_[1]; 
      break;
    case(180): 
      orientation_ = tetromino_[2]; 
      break;     
    case(270): 
      orientation_ = tetromino_[3]; 
      break;
  }
}

// resolve relative position (in grid coordinates) for each block
// coordinates are relative to top left coordinate of 4 x 4 tetromino grid
// order of coordinates is x1, y1, x2, y2, x3, y3, x4, y4 
void Tetromino::resolveRelativePosition() {
  blockPosition_.clear();
  // resolve relative coordinates
  for(int j = 15; j >= 0; --j) {
    if(orientation_[j] == 1) {
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
