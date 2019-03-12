#include "block.hpp"

namespace cpp_tetris {

Block::Block(glm::vec2 gridPosition)
  : gridPosition_{gridPosition} { }

// transform grid position to absolute position (in pixels)
void Block::transformPosition() {
  // size of grid square in pixels
  unsigned grid_size{40};
  // x offset from top left
  unsigned x_offset{20};
  // y offset from top
  unsigned y_offset{20};
  absolutePosition_.x = x_offset + grid_size * gridPosition_.x;
  absolutePosition_.y = y_offset + grid_size * gridPosition_.y;
}

/*
void Block::draw(SpriteRenderer& renderer) {
  renderer.drawSprite(this->sprite_, this->position_, this->size_,
    this->rotation_, this->color_);
}
*/

} // namespace cpp_tetris
