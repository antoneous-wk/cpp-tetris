#include "window.hpp"
#include "shader.hpp"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window);
std::string get_project_path(const std::string& name);

int main(int argc, char* argv[])
{
	cpp_tetris::Init();	
	cpp_tetris::Window win{800, 600, "cpp-tetris"};

	float vertices[]
	{ 
		-0.50f, 0.67f, 0.0f,
		 0.50f, 0.67f, 0.0f,
		 0.50f, 0.33f, 0.0f,
		 0.13f, 0.33f, 0.0f,
		 0.13f,-0.67f, 0.0f,
		-0.13f,-0.67f, 0.0f,
		-0.13f, 0.33f, 0.0f,
		-0.50f, 0.33f, 0.0f
	};		

	unsigned int indices[]
	{
		0, 1, 7,
		1, 2, 7,
		3, 4, 5,
		3, 5, 6	
	};

	// create VAO (vertex array object)
	// create VBO (vertex buffer object)
	// create EBO (element buffer object)
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// VAO must be bound before VBO and EBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// creates new data store (in graphics card memory) for currently bound buffer object
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// specify how OpenGL should interpret vertex attribute data and enable the attribute 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/*
	 * Unbind VAO and VBO
	 * The VAO stores the state since it was first bound.
	 * We are allowed to unbind the VBO because glVertexAttribPointer registered the
     * VBO as the VAO's bound vertex buffer object.
	 * The same cannot be said for the EBO.
	 */ 	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// create shader object
	std::string path{get_project_path(argv[0])};
	cpp_tetris::Shader shader(
	path + "/src/vertex_shader.glsl", 
	path + "/src/fragment_shader.glsl");

	// enable wireframe mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop 
	while(!glfwWindowShouldClose(win.getWin()))
	{
		cpp_tetris::process_input(win.getWin());
		
		// render commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.use();
		shader.setFloat("myColor1", 1.0f, 0.0f, 0.0f, 1.0f);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
		
		/*	
		 * Rendering commands draw to the back buffer to prevent artifacts.	
		 * We must swap the front and back buffers.
		 */
		glfwSwapBuffers(win.getWin());
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
   	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	return 0;
}

	/*
	 * Resolves path of project root directory from argv[0].
	 * Usage: Prepend the return value to the relative path of desired resource file.
	 * Compatible with Unix filesystems.
 	 */
std::string get_project_path(const std::string& name)
{
	// if we are in /build/src directory	
	if (name == "./demo") return "../..";
	// if we are in build directory	
	if (name == "./src/demo") return "..";
	// if we are in project directory
	if (name == "./build/src/demo") return "."; 
	// if we are above or nested above project directory
	std::string project{"cpp-tetris"}; 
	std::string path{name};
	std::size_t pos{name.find(project)};
	if(pos != std::string::npos)
	{	
		path.erase((path.begin()+pos+project.length()), path.end());
		return path;
	}
	// if we are below or nested below build directory
	else if(name[1] == '.')
	{
		pos = name.rfind("../");
		path.erase(path.begin()+pos+3, path.end());
		std::cout << path + ".." << std::endl;
		return path + "..";
	}

	throw std::runtime_error("Please call target from project directory");
}
