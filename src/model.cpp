#include "model.hpp"

namespace cpp_tetris {

Model::Model(ResourceManager& manager)
  : manager_{manager} {}

Model::~Model() {
  for(GameObject* i : bricks_) {
    if(i) {
      delete i;
      i = nullptr;
      std::cout << "Here" << std::endl;
    }
  }
}

void Model::generate() {
  Texture2D texture{manager_.getTexture2D("saw")};
  bricks_.push_back(new GameObject{glm::vec2{0,0}, glm::vec2{100,100}, 
    manager_.getTexture2D("saw"), glm::vec3{1.0f}, glm::vec3{0.0f}});
}

void Model::update() {
  for(GameObject* brick : bricks_)
    brick->move();
}

void Model::draw(SpriteRenderer& renderer) {
  // generate initial brick
  if(bricks_.empty())
    generate(); 
  // generate another brick if previous brick has been placed or destroyed
  if(!bricks_.empty() && ((*--bricks_.end())->isPlaced_ || (*--bricks_.end())->isDestroyed_))
    generate();
  // run draw method for all bricks in bricks_ 
  for(GameObject* brick : bricks_) 
    brick->draw(renderer);
}

} // namespace cpp_tetris
