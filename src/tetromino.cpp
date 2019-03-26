#include "tetromino.hpp"

namespace cpp_tetris {

Tetromino::Tetromino(tetrominoType shape, glm::vec3 color, Texture2D& sprite)
  : shape_{shape}, 
    color_{color},
    angle_{0}, 
    position_{3, -4},
    velocity_{0, 200},
    orientation_{tetrominos[shape_][angle_]},

    isPlaced_{false},
    isDestroyed_{false} {
  // generates (4) blocks to form a tetromino
  generateBlocks(sprite);
}

Tetromino::~Tetromino() {
  for(Block* b : blocks_) {
    if(b) 
      delete b;
  }
}

void Tetromino::moveX(userInput input, float deltaTime) {
  int deltaX{0}; 
  switch(input) {
    case(userInput::KEY_LEFT): {
      if(!detectCollisionX(input))      
        deltaX = -1;
      break;
    }
    case(userInput::KEY_RIGHT): {
      if(!detectCollisionX(input))      
        deltaX = 1;
      break;
    }
  }    
  position_.x += deltaX;
  for(Block* block : blocks_)
    block->moveX(deltaX);
}

void Tetromino::moveY(float deltaTime) {
  static float dy{0.0f};
  dy += velocity_.y * deltaTime;
  if(dy >= grid::SPACING) {
    unsigned deltaY{1};
    position_.y += deltaY;
    for(Block* block : blocks_)
      block->moveY(deltaY);
    dy = 0.0f;
  }
}

void Tetromino::rotate(float deltaTime) {
  // get block coordinates for current tetromino orientation
  // the order of coordinates is {x0, y0}, {x1, y1}, {x2, y2}, {x3, y3}
  vector<glm::vec2> oldBlockCoordinates{getBlockCoordinates(orientation_)};
  // set new tetromino orientation if no collision
  if(angle_ == 270) {
    if(!detectCollisionRotate(0)) {
      angle_ = 0;
      setOrientation(angle_); 
    }
  }
  else if(!detectCollisionRotate(angle_ + 90)) {
      angle_ += 90;
      setOrientation(angle_); 
  }
  else 
  // return if collision
    return;
  // get block coordinates for new tetromino orientation
  vector<glm::vec2> newBlockCoordinates{getBlockCoordinates(orientation_)};
  // calculate deltas and move each block according to respective delta
  vector<glm::vec2>& obc = oldBlockCoordinates;
  vector<glm::vec2>& nbc = newBlockCoordinates;
  vector<glm::vec2> delta =
    {{nbc[0].x - obc[0].x, nbc[0].y - obc[0].y},
     {nbc[1].x - obc[1].x, nbc[1].y - obc[1].y},
     {nbc[2].x - obc[2].x, nbc[2].y - obc[2].y},
     {nbc[3].x - obc[3].x, nbc[3].y - obc[3].y}};
  unsigned i = 0;
  for(Block* block : blocks_) {
    block->moveX(delta[i].x);
    block->moveY(delta[i].y);
    ++i;
  }
}

void Tetromino::draw(SpriteRenderer& renderer) {
  for(Block* block : blocks_) {
    if(block)
      block->draw(renderer);
  }
}

void Tetromino::generateBlocks(Texture2D& sprite) {
  vector<glm::vec2> blockCoordinates{getBlockCoordinates(orientation_)}; 
  for(unsigned i = 0; i < 4; ++i) 
    blocks_.push_back(new Block{blockCoordinates[i], sprite, color_});
}

// Uses current tetromino position and given orientation to determine  
// position for each block in the tetromino (in grid coordinates).
// the order of coordinates is {x0, y0}, {x1, y1}, {x2, y2}, {x3, y3}
vector<glm::vec2> Tetromino::getBlockCoordinates(bitset<16> orientation) {
  vector<glm::vec2> blockCoordinates;
  unsigned xCoordinate = 3;
  unsigned yCoordinate = 3;
  for(unsigned bitPosition = 0; bitPosition < 16; ++bitPosition) {
    if(bitPosition != 0 && bitPosition % 4 == 0) {
      xCoordinate = 3;
      --yCoordinate;
    }
    if(orientation[bitPosition]) {
      blockCoordinates.push_back({xCoordinate + position_.x,
        yCoordinate + position_.y});
    }
    if(xCoordinate > 0)
      --xCoordinate;
  }
  return blockCoordinates;
}

void Tetromino::setOrientation(unsigned angle) {
  angle_ = angle;
  switch(angle_) {
    case(0): 
      orientation_ = tetrominos[shape_][0];
      break;
    case(90): 
      orientation_ = tetrominos[shape_][1]; 
      break;
    case(180): 
      orientation_ = tetrominos[shape_][2]; 
      break;     
    case(270): 
      orientation_ = tetrominos[shape_][3]; 
      break;
  }
}

// transform orientation from single bitset<16> into four bitset<12>
// the transformed bitsets will be used as a bitmask for collision detection
// 0100       000000000100  // bits[3]
// 0100  ---> 000000000100  // bits[2]
// 1100       000000001100  // bits[1]
// 0000       000000000000  // bits[0]
// after transformation, shifts the bits to match tetromino position
// 000000000100       000100000000
// 000000000100  ---> 000100000000 
// 000000001100       001100000000
// 000000000000       000000000000 
vector<bitset<12>> Tetromino::transform(bitset<16> orientation) {
  // transform orientation
  unsigned pos{0};
  unsigned row{0};
  vector<bitset<12>> bits{0, 0, 0, 0};
  for(unsigned b = 0; b < 16; ++b) {
    if(b == 0 || b % 4 != 0) {
      bits[row][pos] = orientation[b];
      ++pos;
    }
    else {
      ++row;
      pos = 0;
      bits[row][pos] = orientation[b];
      ++pos;
    }
  } 
  // shift bits in X direction
  const unsigned offset{bits[0].size() - 5};
  for(bitset<12>& bitRow : bits) {
    if(position_.x <= offset)
      bitRow <<= (offset - position_.x);
    else
      bitRow >>= (position_.x - offset);
  }
  return bits;
}

bool Tetromino::detectCollisionX(userInput input) {
  vector<bitset<12>> bits{transform(orientation_)};
  // detect tetromino collision in the X direction
  if(position_.y >= -3) {
    unsigned gridRow{position_.y + 3};
    switch(input) {
      case(userInput::KEY_LEFT): {
        for(unsigned i = 0; i < 4; ++i) {
          if(((bits[i] << 1) & grid[gridRow]).any())
            return true;
          if(gridRow > 0)
            --gridRow;
        }
        break;
      }
      case(userInput::KEY_RIGHT): {
        for(unsigned i = 0; i < 4; ++i) {
          if(((bits[i] >> 1) & grid[gridRow]).any())
            return true;
          if(gridRow > 0)
            --gridRow;
        }
        break;
      }
    }
  }
  return false;
}

bool Tetromino::detectCollisionY() {
  vector<bitset<12>> bits{transform(orientation_)};
  // detect tetromino collision in the Y direction and update grid
  bool isCollision{false};
  unsigned gridRow{position_.y + 4};
  for(unsigned i = 0; i < 4; ++i) {
    if((bits[i] & grid[gridRow]).any()) 
      isCollision = true;
    if(gridRow > 0)
      --gridRow;
  }
  gridRow = position_.y + 4;
  if(isCollision) {
    for(unsigned i = 0; i < 4; ++i) {
      grid[gridRow-1] = grid[gridRow-1] | bits[i];
      if(gridRow > 0)
        --gridRow; 
    }
  }
  return isCollision;
}

bool Tetromino::detectCollisionRotate(unsigned angle) {
  vector<bitset<12>> bits; 
  switch(angle) {
    case(0):
      bits = transform(tetrominos[shape_][0]);
      break;
    case(90):
      bits = transform(tetrominos[shape_][1]);
      break;
    case(180):
      bits = transform(tetrominos[shape_][2]);
      break;
    case(270):
      bits = transform(tetrominos[shape_][3]);
      break;
  }
  if(position_.y >= -3) {
    unsigned gridRow{position_.y + 3};
      for(unsigned i = 0; i < 4; ++i) {
        if((bits[i] & grid[gridRow]).any())
          return true;
        if(gridRow > 0)
          --gridRow;
      }  
  }
  return false;
}

void Tetromino::destroyBlocks(vector<unsigned> completeRows) {
  for(unsigned row : completeRows) {
    for(Block*& block : blocks_) {
      if(block && block->position_.y == row) { 
        grid[block->position_.y][11-block->position_.x-1] = 0;
        delete block;
        block = nullptr;
      }
    }
  }
  for(unsigned row : completeRows) {
    for(Block* block : blocks_) {
      if(block && block->position_.y < row) { 
        grid[block->position_.y][11-block->position_.x-1] = 0;
        grid[block->position_.y+1][11-block->position_.x-1] = 1;
        block->moveY(1);
      }
    }
  }   
}

// each 16 bit hex number represents a tetromino orientation in 4x4 grid
// there are four blocks per tetromino grid, example:
// 0 1 0 0
// 1 1 0 0
// 0 1 0 0
// 0 0 0 0
const vector<vector<bitset<16>>> Tetromino::tetrominos =
    // 0    // 90   // 180  // 270
  {{0x4640, 0x0E40, 0x4C40, 0x4E00},     // 'tee'
   {0x8C40, 0x6C00, 0x8C40, 0x6C00},     // 'saw'
   {0x4C80, 0xC600, 0x4C80, 0xC600},     // 'zee'
   {0x4444, 0x0F00, 0x4444, 0x0F00},     // 'stick'
   {0x44C0, 0x8E00, 0xC880, 0xE200},     // 'right'
   {0x88C0, 0xE800, 0xC440, 0x2E00},     // 'left'
   {0xCC00, 0xCC00, 0xCC00, 0xCC00}};    // 'box'

// defines a 12 x 17 grid of bits
// grid consists of 0's bounded by 1's on left, right, bottom 
// note: break line for depiction purposes only 
// 1 0 0 0 0 0 0 0 0 0 0 1
// 1 0 0 0 0 0 0 0 0 0 0 1
// ~~~~~(break line)~~~~~~
// 1 0 0 0 0 0 0 0 0 0 0 1
// 1 0 0 0 0 0 0 0 0 0 0 1
// 1 1 1 1 1 1 1 1 1 1 1 1
vector<bitset<12>> Tetromino::grid =
  {0x801, 0x801, 0x801, 0x801, 0x801, 0x801, 0x801, 0x801,
   0x801, 0x801, 0x801, 0x801, 0x801, 0x801, 0x801, 0x801,
   0xFFF};

}  // namespace cpp_tetris
