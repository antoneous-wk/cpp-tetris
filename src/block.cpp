#include "block.hpp"

namespace cpp_tetris {

Block::Block(glm::vec2 position, Texture2D& sprite, glm::vec3 color)
  : position_{position},
    sprite_{sprite},
    color_{color},
    size_{40, 40},
    rotation_{0} { }

void Block::moveY(unsigned deltaY) {
  position_.y += deltaY * grid::SPACING; 
}

void Block::moveX(int deltaX) {
  position_.x += deltaX * grid::SPACING;
}

// transform block coordinates from grid coordinates to screen coordinates (pixels)
// origin (0, 0) is top left corner of screen
void Block::resolveScreenPosition() {
  position_.x = position_.x * grid::SPACING + grid::X_OFFSET;
  position_.y = position_.y * grid::SPACING + grid::Y_OFFSET;
}

void Block::draw(SpriteRenderer& renderer) {
  resolveScreenPosition();  
  renderer.drawSprite(this->sprite_, this->position_, this->size_,
    this->rotation_, this->color_);
}

} // namespace cpp_tetris
