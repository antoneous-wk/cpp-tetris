#ifndef CPP_TETRIS_GAME_OBJECT_HPP
#define CPP_TETRIS_GAME_OBJECT_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "sprite_renderer.hpp"
#include "texture.hpp"
#include <iostream>

using namespace std;

namespace cpp_tetris {

enum userInput {
  LEFT,
  RIGHT,
  DOWN
};

enum gameArea {
  MIN_X = 20,
  MAX_X = 420,
  MIN_Y = 20,
  MAX_Y = 660
};

class GameObject {

  friend class Model;

  public:
    GameObject(glm::vec2 pos, glm::vec2 size, Texture2D& sprite, 
               glm::vec3 color, glm::vec2 velocity);

    void defineLimits();
    void moveY(userInput direction, float deltaTime);
    void moveY(float deltaTime);
    void moveX(userInput direction, float deltaTime);
    void rotate(float deltaTime);
    void draw(SpriteRenderer& renderer);

  private:
    Texture2D& sprite_;
    glm::vec2 position_; 
    glm::vec2 size_;
    glm::vec2 velocity_;
    glm::vec3 color_;
    float rotation_;
    bool isPlaced_;
    bool isDestroyed_;

    unsigned min_x;
    unsigned max_x;
    unsigned min_y;
    unsigned max_y;
   
};

} // namespace cpp_tetris

#endif // header guard
