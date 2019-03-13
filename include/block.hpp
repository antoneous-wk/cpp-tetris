#ifndef CPP_TETRIS_BLOCK_HPP
#define CPP_TETRIS_BLOCK_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "sprite_renderer.hpp"

// foward declaration
class Texture;

namespace cpp_tetris {

class Block {
  public:
    Block(glm::vec2 position, Texture2D& sprite, glm::vec3 color); 

    Block(glm::vec2 gridPosition);
    void draw(SpriteRenderer& renderer);
  private:
    glm::vec2 position_;
    Texture2D& sprite_;
    glm::vec3 color_;
    glm::vec2 size_;
    glm::vec2 velocity_;
    float rotation_;
    //bool isDestroyed_;
};

} // namespace cpp_tetris

#endif // header guard
