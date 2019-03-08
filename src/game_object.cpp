#include "game_object.hpp"

namespace cpp_tetris {

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D& sprite,
                       glm::vec3 color, glm::vec2 velocity)
  : position_{pos}, size_{size}, velocity_{velocity}, color_{color}, 
    rotation_{0.0f}, sprite_{sprite}, isPlaced_{false}, isDestroyed_{false} { 

  defineLimits();
} 

// define max and min coordinates for each brick 
void GameObject::defineLimits() {

  if(rotation_ == 0.0f || rotation_ == 180.0f) {  
    min_x = gameArea::MIN_X;
    max_x = gameArea::MAX_X - size_.x;
    min_y = gameArea::MIN_Y;
    max_y = gameArea::MAX_Y - size_.y;
  }

  if(rotation_ == 90.0f || rotation_ == 270.0f) {
    min_x = gameArea::MIN_X;
    if(static_cast<int>(size_.x) % 2 == 0)
      max_x = gameArea::MAX_X - size_.x + size_.y/2;
//    else 
//      max_x = gameArea::MAX_X - size_.x + 20; 
    min_y = gameArea::MIN_Y;
    max_y = gameArea::MAX_Y;
  }
}

// defines automatic block movement in the y direction
void GameObject::moveY(float deltaTime) {
  static float dy{0.0f};
  dy += velocity_.y * deltaTime;
  if(dy >= 20) {
    position_.y += 20;
    dy = 0.0f;
  }
}

// defines manual block movement in the y direction
void GameObject::moveY(userInput direction, float deltaTime) {
  static float dy{0.0f};
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
  static float dx{0.0f};
  dx += velocity_.x * deltaTime;
  if(dx >= 40) {
    defineLimits();
    if(direction == userInput::RIGHT && position_.x != max_x)   
      position_.x += 40;
      std::cout << position_.x << std::endl;
    if(direction == userInput::LEFT && position_.x != min_x) 
      position_.x -= 40; 
    dx = 0.0f;
  }
}

// defines block rotation
void GameObject::rotate(float deltaTime) {
  static float dr{0.0f};
  dr += 1000 * deltaTime;

  if(dr >= 90) {
    rotation_ += 90.f;
    if(rotation_ == 360.0f)
      rotation_ = 0.0f;
    dr = 0.0f; 
  }
  defineLimits();
  std::cout << position_.x << std::endl;
}

void GameObject::draw(SpriteRenderer& renderer) {
  renderer.drawSprite(this->sprite_, this->position_, this->size_,
    this->rotation_, this->color_);
}

}  // namespace cpp_tetris
