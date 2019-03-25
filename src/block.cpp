#include "block.hpp"

namespace cpp_tetris {

Block::Block(glm::vec2 position, Texture2D& sprite, glm::vec3 color)
  : position_{position},
    sprite_{sprite},
    color_{color},
    size_{40, 40},
    isDestroyed_{false},
    rotation_{0} { }

void Block::draw(SpriteRenderer& renderer) {
  if(!isDestroyed_) {
  renderer.drawSprite(this->sprite_, resolveScreenCoordinates(), this->size_,
    this->rotation_, this->color_);
  }
}

void Block::moveX(int deltaX) {
  position_.x += deltaX;
}

void Block::moveY(int deltaY) {
  position_.y += deltaY;
}


// transform block position from grid coordinates to screen coordinates (pixels)
// origin (0, 0) is top left corner of screen
glm::vec2 Block::resolveScreenCoordinates() {
  glm::vec2 position;
  position.x = position_.x * grid::SPACING + grid::X_OFFSET;
  position.y = position_.y * grid::SPACING + grid::Y_OFFSET;
  return position;
}

} // namespace cpp_tetris
