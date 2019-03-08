#include "sprite_renderer.hpp"

namespace cpp_tetris {

SpriteRenderer::SpriteRenderer(Shader& shader)
  : shader_{shader} {
  initRenderData();
}

SpriteRenderer::~SpriteRenderer() {
  glDeleteVertexArrays(1, &quadVAO_);
}

void SpriteRenderer::drawSprite(Texture2D& texture, glm::vec2 position, 
								glm::vec2 size, float degrees, glm::vec3 color) {
  this->shader_.useProgram();
  glm::mat4 model;
  model = glm::translate(model, glm::vec3(position, 0.0f));

  // we have defined our origin at (0,0) (top left)
  // rotations always revolve around top left point 
  // we must translate the sprite before and after rotation
  model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
  model = glm::rotate(model, glm::radians(degrees), glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

  model = glm::scale(model, glm::vec3(size, 1.0f));

  this->shader_.setUniformMatrix4f("model", model);
  this->shader_.setUniform3f("spriteColor", color);

  glActiveTexture(GL_TEXTURE0);
  texture.bind();

  glBindVertexArray(this->quadVAO_);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

void SpriteRenderer::initRenderData() {
  unsigned VBO;
  float vertices[]{
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f
  };

  glGenVertexArrays(1, &this->quadVAO_);
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(this->quadVAO_);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), 
    (GLvoid*)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

} // namespace cpp_tetris
