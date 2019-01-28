#include "window.hpp"
#include "shader.hpp"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window);

int main()
{
	cpp_tetris::Init();	
	cpp_tetris::Window win{800, 600, "cpp-tetris"};
	
	float vertices[]{ 
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};		

	/* create VAO (vertex array object) and VBO (vertex buffer object) */
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	/* VAO must be bound before VBO */
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/* creates new data store (in graphics card memory) for currently bound buffer object */
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/* specify how OpenGL should interpret vertex attribute data and enable the attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/*
	 * Unbind VAO and VBO
     *
	 * The VAO stores the state since it was first bound
     *
	 */ 	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/* create shader object */
	cpp_tetris::Shader shader(
	"/home/gummo/Local-Repo/cpp-tetris/src/vertex_shader.s", 
	"/home/gummo/Local-Repo/cpp-tetris/src/fragment_shader.s");

	/* render loop */
	while(!glfwWindowShouldClose(win.getWin()))
	{
		cpp_tetris::process_input(win.getWin());
		
		/* render commands */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		/*	
		 * Rendering commands draw to the back buffer to prevent artifacts.	
		 * We must swap the front and back buffers.
		 *
		 */
		glfwSwapBuffers(win.getWin());

		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
   	glDeleteBuffers(1, &VBO);

//	glfwTerminate();

	return 0;
}

