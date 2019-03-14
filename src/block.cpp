#include "block.hpp"

namespace cpp_tetris {

Block::Block(glm::vec2 position, Texture2D& sprite, glm::vec3 color)
  : position_{position},
    sprite_{sprite},
    color_{color},
    size_{40, 40},
    rotation_{0} { }

void Block::moveY(unsigned deltaY) {
  position_.y += deltaY; 
}

void Block::moveX(int deltaX) {
  position_.x += deltaX;
}

void Block::draw(SpriteRenderer& renderer, glm::vec2 position) {
  position_ = position;
  renderer.drawSprite(this->sprite_, this->position_, this->size_,
    this->rotation_, this->color_);
}

} // namespace cpp_tetris
