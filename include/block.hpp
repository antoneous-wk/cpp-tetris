#ifndef CPP_TETRIS_BLOCK_HPP
#define CPP_TETRIS_BLOCK_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "sprite_renderer.hpp"

// foward declaration
class Texture;
class Tetromino;

enum grid {
  X_OFFSET = 20,
  Y_OFFSET = 20,
  SPACING = 40,
};

namespace cpp_tetris {

class Block {
  friend class Tetromino;
  public:
    Block(glm::vec2 position, Texture2D& sprite, glm::vec3 color); 
    Block(glm::vec2 gridPosition);
    void draw(SpriteRenderer& renderer, glm::vec2 position);
    void draw(SpriteRenderer& renderer);
    void moveY(unsigned deltaY);
    void moveX(int deltaX);
    void resolveScreenPosition(); 
  private:
    glm::vec2 position_;
    Texture2D& sprite_;
    glm::vec3 color_;
    glm::vec2 size_;
    float rotation_;
};

} // namespace cpp_tetris

#endif // header guard
