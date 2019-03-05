#include "game_object.hpp"

namespace cpp_tetris {

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D& sprite,
                       glm::vec3 color, glm::vec2 velocity)
  : position_{pos}, size_{size}, velocity_{velocity}, color_{color}, 
    rotation_{0.0f}, sprite_{sprite}, isPlaced_{false}, isDestroyed_{false} { 

  // define maximum coordinates for each GameObject
  min_x = gameArea::MIN_X;
  max_x = gameArea::MAX_X - size.x;
  min_y = gameArea::MIN_Y;
  max_y = gameArea::MAX_Y - size.y;
} 

// defines automatic block movement in the y direction
void GameObject::moveY(float deltaTime) {
  static float dy = 0.0f;
  dy += velocity_.y * deltaTime;
  if(dy >= 20) {
    position_.y += 20;
    dy = 0.0f;
  }
}

// defines manual block movement in the y direction
void GameObject::moveY(userInput direction, float deltaTime) {
  static float dy = 0.0f;

  // uses x component of velocity
  dy += velocity_.x * deltaTime;
  if(dy >= 20) {
    if(direction == userInput::DOWN)
      position_.y += 20;
    dy = 0.0f;
  }
}

// defines lateral block movement
void GameObject::moveX(userInput direction, float deltaTime) {
  static float dx = 0.0f;
  dx += velocity_.x * deltaTime;
  if(dx >= 40) {
    if(direction == userInput::RIGHT && position_.x != max_x)   
      position_.x += 40;
    if(direction == userInput::LEFT && position_.x != min_x) 
      position_.x -= 40; 
    dx = 0.0f;
  }
}

void GameObject::rotate(float deltaTime) { }

void GameObject::draw(SpriteRenderer& renderer) {
  renderer.drawSprite(this->sprite_, this->position_, this->size_,
    this->rotation_, this->color_);
}

}  // namespace cpp_tetris
