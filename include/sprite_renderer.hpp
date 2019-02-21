#ifndef CPP_TETRIS_SPRITE_RENDERER_HPP
#define CPP_TETRIS_SPRITE_RENDERER_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "texture.hpp"
#include "shader.hpp"


namespace cpp_tetris {

class SpriteRenderer {
  public:
    SpriteRenderer(Shader& shader);
    ~SpriteRenderer();

    void drawSprite(Texture2D& texture, glm::vec2 position, 
					glm::vec2 size = glm::vec2(10,10), float degrees = 0.0f,
					glm::vec3 color = glm::vec3(1.0f));
  private:
	void initRenderData();

    Shader shader_;
	unsigned quadVAO_;
};

} // namespace cpp_tetris

#endif // header guard
