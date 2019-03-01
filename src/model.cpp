#include "model.hpp"

namespace cpp_tetris {

Model::Model(ResourceManager& manager)
  : manager_{manager} {}

Model::~Model() {

  unsigned count{0};
  for(GameObject* i : bricks_) {
    if(i) {
      delete i;
      i = nullptr;
      ++count;
    }
  }
  std::cout << count << "bricks were generated" << std::endl;
}

void Model::generate() {
  //Texture2D texture{manager_.getTexture2D("saw")};
  bricks_.push_back(new GameObject{glm::vec2{0,0}, glm::vec2{40,40}, 
    manager_.getTexture2D("test_block"), glm::vec3{0.0f, 1.0f, 0.0f}, glm::vec3{0.0f}});
}

void Model::update() {
  for(GameObject* brick : bricks_) {
    if(brick->position_.y >= 500)  
      brick->isPlaced_ = true;
    if(!brick->isPlaced_)
      brick->move();
  }
}

void Model::draw(SpriteRenderer& renderer) {
  // generate initial brick
  if(bricks_.empty())
    generate(); 
  // generate another brick if previous brick has been placed or destroyed
  if(!bricks_.empty() && (*--bricks_.end())->isPlaced_)
    generate();
  // run draw method for all bricks in bricks_ 
  for(GameObject* brick : bricks_) 
    brick->draw(renderer);
}

} // namespace cpp_tetris
