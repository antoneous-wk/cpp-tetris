#include "game.hpp"

namespace cpp_tetris {

Game::Game(ResourceManager& manager, int width, int height)
  : state_{GAME_ACTIVE}, width_{width}, height_{height}, manager_{manager}, 
    win_{nullptr}, model_{nullptr}, controller_{nullptr}, renderer_{nullptr} { }

Game::~Game() {
  if(model_)
    delete model_;
  model_ = nullptr;
 
  if(controller_)
    delete controller_;
  controller_ = nullptr;

  if(renderer_)
    delete renderer_;
  renderer_ = nullptr;

  if(win_)
    delete win_;
  win_ = nullptr;
}

void Game::init() {
  // create window and initialize
  win_ = new Window{width_, this->height_, "cpp-tetris"};
  win_->init();
 
  // model_ manages game logic
  model_ = new Model(manager_);

  // controller_ manages user input
  controller_ = new Controller(win_->getWin());

  // load shaders
  manager_.loadShader("sprite", "src/sprite_vertex_shader.glsl",
    "src/sprite_fragment_shader.glsl");

  // configure shaders
  glm::mat4 projection{glm::ortho(0.0f, static_cast<float>(width_), 
    static_cast<float>(height_), 0.0f, -1.0f, 1.0f)};
  manager_.getShader("sprite").useProgram();
  manager_.getShader("sprite").setUniform1ui("image", 0);
  manager_.getShader("sprite").setUniformMatrix4f("projection", projection);

  // load background textures
  manager_.loadTexture2D("bground_layer0", "resources/textures/bgroundl0.png", 
    GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGBA);
  manager_.loadTexture2D("bground_layer1", "resources/textures/bgroundl1.png",
    GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER, GL_LINEAR, GL_LINEAR, GL_RGBA);
  manager_.loadTexture2D("grid_layer2", "resources/textures/grid.png",
    GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER, GL_LINEAR, GL_LINEAR, GL_RGBA);

  // load block textures 
  manager_.loadTexture2D("left", "resources/textures/left.png",
    GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER, GL_LINEAR, GL_LINEAR, GL_RGBA);
  manager_.loadTexture2D("right", "resources/textures/right.png",
    GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER, GL_LINEAR, GL_LINEAR, GL_RGBA);
  manager_.loadTexture2D("stick", "resources/textures/stick.png",
    GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER, GL_LINEAR, GL_LINEAR, GL_RGBA);
  manager_.loadTexture2D("tee", "resources/textures/tee.png",
    GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER, GL_LINEAR, GL_LINEAR, GL_RGBA);
  manager_.loadTexture2D("zee", "resources/textures/zee.png",
    GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER, GL_LINEAR, GL_LINEAR, GL_RGBA);
  manager_.loadTexture2D("saw", "resources/textures/saw.png",
    GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER, GL_LINEAR, GL_LINEAR, GL_RGBA);
  manager_.loadTexture2D("box", "resources/textures/box.png",
    GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER, GL_LINEAR, GL_LINEAR, GL_RGBA);

  renderer_ = new SpriteRenderer{manager_.getShader("sprite")};
}

void Game::processInput() { 
  controller_->processInput();
}
 
void Game::update(float deltaTime) { 
  model_->update(*controller_, deltaTime);
}

void Game::render(float deltaTime) {
  if(state_ == GAME_ACTIVE) {  
    // draw background layers
    renderer_->drawSprite(manager_.getTexture2D("bground_layer0"), 
      glm::vec2(0, 0), glm::vec2(width_, height_));
    renderer_->drawSprite(manager_.getTexture2D("bground_layer1"),
      glm::vec2(0, 0), glm::vec2(width_, height_));
    renderer_->drawSprite(manager_.getTexture2D("grid_layer2"),
      glm::vec2(0, 0), glm::vec2(width_, height_));
    
    // draw GameObjects
    model_->draw(*renderer_, deltaTime);
  }
}
    

} // namespace cpp_tetris
