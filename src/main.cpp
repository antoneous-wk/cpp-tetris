#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "window.hpp"
#include "shader.hpp"
#include <iostream>

// must define before including stb_image.h
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window);
std::string get_project_path(const std::string& name);

int main(int argc, char* argv[])
{
	cpp_tetris::Init();	
	cpp_tetris::Window win{800, 600, "cpp-tetris"};
	
	float vertices[]
	{	// position			// colors			// texture coords
		0.5f,  0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
	   -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
	   -0.5f,  0.5f, 0.0f,	1.0f, 1.0f, 0.0f,	0.0f, 1.0f
	};

	unsigned int indices[]
	{
		0, 1, 3,
		1, 2, 3
	};	

	/*
	 * create VAO (vertex array object)
	 * create VBO (vertex buffer object)
	 * create EBO (element buffer object)
	 */
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	/* VAO must be bound before VBO and EBO */
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	/* creates new data store (in graphics card memory) for currently bound buffer object */
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	/* specify how OpenGL should interpret vertex attribute data and enable the attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 
		(void*) (3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
		(void*) (6 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	/*
	 * Unbind VAO and VBO
	 * The VAO stores the state since it was first bound.
	 * We are allowed to unbind the VBO because glVertexAttribPointer registered the
     * VBO as the VAO's bound vertex buffer object.
	 * The same cannot be said for the EBO.
	 */ 	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/* get project path	*/
	const std::string path{get_project_path(argv[0])};

	/* generate and bind texture object */
	unsigned int texture;
	glGenTextures(1, &texture);	
	glBindTexture(GL_TEXTURE_2D, texture);

	/* set the texture wrapping/filtering options (for currently bound texture) */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/* load texture image */
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char *data{
		stbi_load((path + "/resources/textures/chile.png").c_str(), 
		&width, &height, &nrChannels, 0)};

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	/* create shader object */
	cpp_tetris::Shader shader(
	path + "/src/vertex_shader.glsl", 
	path + "/src/fragment_shader.glsl");

	/* glm::mat4 constructor that takes a single value constructs diagonal (identity) matrix */
	glm::mat4 trans{1.0f};
	
	/* enable wireframe mode */
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* render loop */
	while(!glfwWindowShouldClose(win.getWin()))
	{
		cpp_tetris::process_input(win.getWin());
		
		/* render commands */
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.use();
		trans = glm::rotate(trans, glm::radians(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		shader.setMatrix4fv("transform", trans);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 6); 
		
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
	/* if we are in /build/src directory */
	if (name == "./demo") return "../..";
	/* if we are in build directory	*/
	if (name == "./src/demo") return "..";
	/* if we are in project directory */
	if (name == "./build/src/demo") return "."; 
	/* if we are above or nested above project directory */
	std::string project{"cpp-tetris"}; 
	std::string path{name};
	std::size_t pos{name.find(project)};
	if(pos != std::string::npos)
	{	
		path.erase((path.begin()+pos+project.length()), path.end());
		return path;
	}
	/* if we are below or nested below build directory */
	else if(name[1] == '.')
	{
		pos = name.rfind("../");
		path.erase(path.begin()+pos+3, path.end());
		std::cout << path + ".." << std::endl;
		return path + "..";
	}

	throw std::runtime_error("Please call target from project directory");
}
