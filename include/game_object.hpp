#ifndef CPP_TETRIS_GAME_OBJECT_HPP
#define CPP_TETRIS_GAME_OBJECT_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "sprite_renderer.hpp"
#include "texture.hpp"
#include "model.hpp"

using namespace std;

namespace cpp_tetris {

class GameObject {
  public:
    GameObject(Texture2D& sprite);
    virtual ~GameObject() = default;
    GameObject(glm::vec2 pos, glm::vec2 size, Texture2D& sprite, 
               glm::vec3 color, glm::vec2 velocity);
    virtual void draw(SpriteRenderer& renderer);

  protected:
    glm::vec2 position_, size_, velocity_;
    glm::vec3 color_;
    float rotation_;
    bool isSolid_;
    bool destroyed_;

    Texture2D& sprite_;
};

} // namespace cpp_tetris

#endif // header guard
