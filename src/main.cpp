#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}	

int main()
{
	glfwInit();

	/* 
	 * Set window creation hints. 
	 *  
	 * Creation hints are reset every time glfwInit is called.
	 * Set minor and major versions of OpenGL to 3.
	 * Set OpenGL profile to core-profile.
	 *
     */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* 
	 * Create window object and its associated OpenGL context.
	 *
	 * An OpenGL context stores the state associated with a single instance of OpenGL.
	 * Before context can be used it must be made current with glfwMakeConextCurrent()
	 *
	 */
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		return -1;
	}
	
	glfwMakeContextCurrent(window);

	/*
	 * glfwGetProcAddress function returns address of a specified OpenGL function pointer.
	 * The returned address is implicitly converted to pointer by C++
	 * The pointer is then explictly cast to GLADloadproc type defined in glad.h
	 *
	 */
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))	
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	/*	
	 * \args: x, y, width, height
	 * 
	 * x,y specify lower left corner of viewport rectangle (in normalized device coordinates)
	 * width, height specify width and height of viewport (in window coordinates)
	 *
	 */
	glViewport(0, 0, 800, 600);
	
	/*
	 * Register the callback function that gets called by GLFW when window is resized.
	 *
     * Resizes the viewport based on new window size.
	 * Callback functions registered after window creation and before render loop.
	 *
	 */
	 glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	 
	float vertices[]{ 
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};		

	/*
	 * Create vertex buffer object 
	 *
	 * \prototype: void glGenBuffers(GLsizei n, GLUint* buffers)
	 * glGenBuffers generates unique name for each n, stores each name in buffers array.
	 * glBindBuffer associates a buffer binding target with each name in array.
	 *
	 */
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/* render loop */
	while(!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		/* render commands */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	
		/*	
		 * Rendering commands draw to the back buffer to prevent artifacts.	
		 * We must swap the front and back buffers.
		 *
		 */
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}


