#include "model.hpp"

namespace cpp_tetris {

Model::Model(ResourceManager& manager)
  : manager_{manager} {}

Model::~Model() {
  for(GameObject* i : bricks_) {
    if(i) {
      delete i;
      i = nullptr;
    }
  }
}

void Model::generate() {
  unsigned number_of_bricks{brickType::NUM_OF_TYPES-1};
  // create new engine & seed it 
  static default_random_engine e{time(0)};
  // generate random distribution from 0 to num_of_bricks inclusive
  static uniform_int_distribution<unsigned> u{0, number_of_bricks};

  std::string brick_name;
  glm::vec3 color;
  glm::vec2 size; 

  switch(u(e)) {
    case (brickType::B_LEFT):
      brick_name = "left";
      color = {1.0f, 0.5f, 0.0f}; // orange
      size = {160, 80};
      break;
    case (brickType::B_RIGHT):
      brick_name = "right";
      color = {0.0f, 0.0f, 1.0f}; // blue
      size = {160, 80};
      break;
    case (brickType::B_STICK):
      brick_name = "stick";
      color = {0.3f, 1.0f, 1.0f}; // cyan
      size = {160, 40};
      break;
    case (brickType::B_TEE):
      brick_name = "tee";
      color = {1.0f, 0.3f, 1.0f}; // pink
      size = {120, 80};
      break;
    case (brickType::B_ZEE):
      brick_name = "zee";
      color = {1.0f, 0.0f, 0.0f}; // red
      size = {120, 80};
      break;
    case (brickType::B_SAW):
      brick_name = "saw";
      color = {0.3f, 1.0f, 0.3f}; // green
      size = {120, 80};
      break;
    case (brickType::B_BOX):
      brick_name = "box";
      color = {1.0f, 1.0f, 0.3f}; // yellow
      size = {80, 80};
      break;
  }

  bricks_.push_back(new GameObject{glm::vec2{20, 0}, size, 
    manager_.getTexture2D(brick_name), color, glm::vec2{500.0f, 60.0f}});
}

void Model::update(Controller& controller, float deltaTime) {
  // generate initial brick
  if(bricks_.empty())
    generate(); 
  // generate another brick if previous brick has been placed or destroyed
  if(!bricks_.empty() && (*--bricks_.end())->isPlaced_)
    generate();

  for(GameObject* brick : bricks_) {
    if(brick->position_.y >= 500)  
      brick->isPlaced_ = true;
    if(!brick->isPlaced_) {
      controller.processInput(*brick, deltaTime);
      brick->moveY(deltaTime);
    }
  }
}

void Model::draw(SpriteRenderer& renderer, float deltaTime) {
  // run draw method for all bricks in bricks_ 
  for(GameObject* brick : bricks_) 
    brick->draw(renderer);
  }  

} // namespace cpp_tetris
