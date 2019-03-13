#include "block.hpp"

namespace cpp_tetris {

Block::Block(glm::vec2 position, Texture2D& sprite, glm::vec3 color)
  : position_{position},
    sprite_{sprite},
    color_{color},
    size_{40, 40},
    velocity_{0},
    rotation_{0} { }


/*
void Block::draw(SpriteRenderer& renderer) {
  renderer.drawSprite(this->sprite_, this->position_, this->size_,
    this->rotation_, this->color_);
}
*/

} // namespace cpp_tetris
