#ifndef CPP_TETRIS_BLOCK_HPP
#define CPP_TETRIS_BLOCK_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "sprite_renderer.hpp"
#include "texture.hpp"

namespace cpp_tetris {

class Block {
  public:
    /*
    Block(glm::vec2 pos, glm::vec2 size, Texture2D& sprite, glm::vec3 color, 
          glm::vec2 velocity);
    */
    Block(glm::vec2 gridPosition);
    void draw(SpriteRenderer& renderer);
  private:
    void transformPosition();
    glm::vec2 gridPosition_;
    glm::vec2 absolutePosition_;

    //Texture2D& sprite_;
    //glm::vec2 size_;
    //glm::vec2 velocity_;
    //glm::vec3 color_;
    //float rotation_;
    //bool isPlaced_;
    //bool isDestroyed_;
};

} // namespace cpp_tetris

#endif // header guard
