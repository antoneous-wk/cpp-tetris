#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "resource_manager.hpp"
#include "window.hpp"
#include "game.hpp"

//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void process_input(GLFWwindow *window);

int main(int argc, char* argv[]) {
  cpp_tetris::ResourceManager resource_manager{"./src/demo"};
  cpp_tetris::Game game{resource_manager, 800, 600};
  game.init();
  return 0;
}


//  cpp_tetris::Init();	
//  cpp_tetris::Window win{800, 600, "cpp-tetris"};
//  cpp_tetris::ResourceManager rm(argv[0]);
//
//  rm.loadShader("myProgram", "src/vertex_shader.glsl", "src/fragment_shader.glsl");
//  rm.loadTexture2D("stick", "resources/textures/box.png", GL_REPEAT, GL_REPEAT,
//    GL_LINEAR, GL_LINEAR, GL_RGBA);
//
//  /* create block instance */
//  cpp_tetris::Block block{rm};
//  block.Init();
//
//  /* glm::mat4 constructor that takes a single value constructs diagonal (identity) matrix */
//  glm::mat4 trans{1.0f};
//	
//  glEnable(GL_BLEND);
//  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//  cpp_tetris::Shader& shader = rm.getShader("myProgram");
//
//  /* render loop */
//  while(!glfwWindowShouldClose(win.getWin())) {
//    cpp_tetris::process_input(win.getWin());
//	/* render commands */
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT);
//	shader.useProgram();	
//	trans = glm::rotate(trans, glm::radians(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
//	shader.setUniformMatrix4fv("transform", trans);
//
//	glBindVertexArray(block.getVAO());
//	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//	glDrawArrays(GL_TRIANGLES, 0, 6); 
//		
//	/*	
//	 * Rendering commands draw to the back buffer to prevent artifacts.	
//	 * We must swap the front and back buffers.
//	 */
//	glfwSwapBuffers(win.getWin());
//	glfwPollEvents();
//  }
//
//}
//
//// glDeleteVertexArrays(1, &VAO);
//// glDeleteBuffers(1, &VBO);
//
//  return 0;
//}
