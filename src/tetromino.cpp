#include "tetromino.hpp"

namespace cpp_tetris {

Tetromino::Tetromino(unsigned tetromino, Texture2D& sprite)
  : isPlaced_{false} {
  setAttributes(tetromino);
  // resolve block coordinates at 0 deg orientation
  resolveBlockCoordinates(0);    
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

void Tetromino::setAttributes(unsigned tetromino) {
  // set starting position for tetromino
  tetrominoCoordinates_ = {4, 0};
  tetromino_ = tetrominos[tetromino];
  switch(tetromino) {
    case (tetrominoType::left):
      color_ = {1.0f, 0.5f, 0.0f}; // orange
      break;
    case (tetrominoType::right):
      color_ = {0.0f, 0.0f, 1.0f}; // blue
      break;
    case (tetrominoType::stick):
      color_ = {0.3f, 1.0f, 1.0f}; // cyan
      break;
    case (tetrominoType::tee):
      color_ = {1.0f, 0.3f, 1.0f}; // pink
      break;
    case (tetrominoType::zee):
      color_ = {1.0f, 0.0f, 0.0f}; // red
      break;
    case (tetrominoType::saw):
      color_ = {0.3f, 1.0f, 0.3f}; // green
      break;
    case (tetrominoType::box):
      color_ = {1.0f, 1.0f, 0.3f}; // yellow
      break;
  }
}

// resolve coordinates for each block
// coordinates are relative to top left coordinate of 4 x 4 tetromino grid
// order of coordinates is x1, y1, x2, y2, x3, y3, x4, y4 
void Tetromino::resolveBlockCoordinates(unsigned orientation) {
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
        blockCoordinates_.push_back(0); 
      else if(j % 2 == 0 && j % 4 != 0) 
        blockCoordinates_.push_back(1); 
      else if(j % 4 == 0) 
        blockCoordinates_.push_back(3); 
      else 
        blockCoordinates_.push_back(2); 
      // resolve relative y (row) coordinate for each block
      if(j >= 12) 
        blockCoordinates_.push_back(0); 
      else if(j >= 8) 
        blockCoordinates_.push_back(1); 
      else if(j >= 4) 
        blockCoordinates_.push_back(2); 
      else 
        blockCoordinates_.push_back(3); 
   } 
  }
  
  unsigned x_offset = 20;
  unsigned y_offset = 20;
  unsigned grid_spacing = 40;
  // resolve absolute coordinates
  for(unsigned j = 0; j < 7; j+=2) {
    blockCoordinates_[j] += tetrominoCoordinates_.x;
    blockCoordinates_[j] = blockCoordinates_[j] * grid_spacing + x_offset;
    blockCoordinates_[j+1] += tetrominoCoordinates_.y;
    blockCoordinates_[j+1] = blockCoordinates_[j+1] * grid_spacing + y_offset; 
  }
/*
  for(unsigned j = 0; j < 7; j+=2)
    std::cout << blockCoordinates_[j] << " " << blockCoordinates_[j+1] << endl;
*/
}

void Tetromino::generateBlocks(Texture2D& sprite) {
  for(unsigned j = 0; j < 7; j+=2) {
    blocks_.push_back(new Block{glm::vec2{blockCoordinates_[j],
      blockCoordinates_[j+1]}, sprite, color_});
  }
}

}  // namespace cpp_tetris
