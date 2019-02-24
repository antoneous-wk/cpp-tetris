#include "game.hpp"

namespace cpp_tetris {

Game::Game(ResourceManager& manager, int width, int height)
  : state_{GAME_ACTIVE}, keys_{}, width_{width}, height_{height},
    manager_{manager}, win_{nullptr}, renderer_{nullptr} { }

Game::~Game() {
  if(renderer_)
    delete renderer_;
  renderer_ = nullptr;

  if(win_)
    delete win_;
  win_ = nullptr;
}

void Game::init() {
  // create window and initialize
  win_ = new Window{this->width_, this->height_, "cpp-tetris"};
  win_->init();
   
  // load shaders
  manager_.loadShader("sprite", "src/sprite_vertex_shader.glsl",
    "src/sprite_fragment_shader.glsl");

  // configure shaders
  glm::mat4 projection{glm::ortho(0.0f, static_cast<float>(this->width_), 
    static_cast<float>(this->height_), 0.0f, -1.0f, 1.0f)};
  this->manager_.getShader("sprite").useProgram();
  this->manager_.getShader("sprite").setUniform1ui("image", 0);
  this->manager_.getShader("sprite").setUniformMatrix4f("projection", projection);

  // load textures
  this->manager_.loadTexture2D("zee", "resources/textures/zee.png", GL_REPEAT,
    GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGBA);
  
  renderer_ = new SpriteRenderer{this->manager_.getShader("sprite")};
}

void Game::processInput() { }

void Game::update(float delta_time) { }

void Game::render(float delta_time) {
  renderer_->drawSprite(manager_.getTexture2D("zee"), glm::vec2(0, 0), 
    glm::vec2(50, 50), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}
    

} // namespace cpp_tetris
