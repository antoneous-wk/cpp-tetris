#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

/* vertex shader */
const char* vertexShaderSource = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

/* fragment shader */
const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

int main()
{
	glfwInit();

	/* 
	 * Set window creation hints 
	 *  
	 * Creation hints are reset every time glfwInit is called
	 * Set minor and major versions of OpenGL to 3
	 * Set OpenGL profile to core-profile
	 *
     */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* 
	 * Create window object and its associated OpenGL context
	 *
	 * An OpenGL context stores the state associated with a single instance of OpenGL
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
	 * glfwGetProcAddress function returns address of a specified OpenGL function pointer
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
	 * x,y specify lower left corner of viewport rectangle (normalized device coordinates)
	 * width, height specify width and height of viewport (window coordinates)
	 
	 */
	glViewport(0, 0, 800, 600);

	/*
	 * Register the callback function that gets called by GLFW when window is resized
	 *
     * Resizes the viewport based on new window size
	 * Callback functions registered after window creation and before render loop
	 *
	 */
	 glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

///////////////////////////* start shader creation */////////////////////////////////////////

	/*
	 * Create vertex shader object 
	 *
	 * glShaderSource sets sets source code in shader to source in vertexShaderSource
	 * glCompileShader compiles the source code stored in shader
	 *
	 */
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	/* check to see if compilation was successful */
	int success_vs;
	char infoLog_vs[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success_vs);
	if(!success_vs)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog_vs);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog_vs << std::endl;
	}

	/*
	 * Create fragment shader object 
	 * 
	 * glShaderSource sets source code in shader to source in fragmentShaderSource
	 * glCompileShader compiles the source code stored in shader
	 *
	 */
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	/* check to see if compilation was successful */
	int success_fs;	
	char infoLog_fs[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success_fs);
	if(!success_fs)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog_fs);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog_fs << std::endl;
	}	

	/* after compiling the shaders, we must link them into a program */
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	/* check to see if linking was successful */
	int success_sp;
	char infoLog_sp[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success_sp);
	if(!success_sp)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog_sp);
	}	

	/* delete shader objects (we don't need them anymore) */
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

///////////////////////////////* start set up for render */////////////////////////////////// 

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

////////////////////////////////* end setup up for render *//////////////////////////////////

	/* render loop */
	while(!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		/* render commands */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		/*	
		 * Rendering commands draw to the back buffer to prevent artifacts.	
		 * We must swap the front and back buffers.
		 *
		 */
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
   	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}	
