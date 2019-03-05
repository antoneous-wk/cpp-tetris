#include "game_object.hpp"

namespace cpp_tetris {

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D& sprite,
                       glm::vec3 color, glm::vec2 velocity)
  : position_{pos}, size_{size}, velocity_{velocity}, color_{color}, 
    rotation_{0.0f}, sprite_{sprite}, isPlaced_{false}, isDestroyed_{false} { } 

void GameObject::moveY(float deltaTime) {
  static float dy = 0.0f;
  dy += velocity_.y * deltaTime;
  if(dy >= 20) {
    position_.y += 20;
    dy = 0.0f;
  }
}

void GameObject::moveX(userInput direction, float deltaTime) {
  static float dx = 0.0f;
  dx += velocity_.x * deltaTime;
  if(dx>=40) {
    if(direction == userInput::RIGHT)   
      position_.x += 40;
    if(direction == userInput::LEFT) 
      position_.x -= 40; 
    dx = 0.0f;
  }
}

void GameObject::draw(SpriteRenderer& renderer) {
  renderer.drawSprite(this->sprite_, this->position_, this->size_,
    this->rotation_, this->color_);
}

}  // namespace cpp_tetris
