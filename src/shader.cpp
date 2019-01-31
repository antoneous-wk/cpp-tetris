#include "shader.hpp"
#include <stdexcept>

namespace cpp_tetris
{

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;
		
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();
		
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch(const std::ifstream::failure& e)
	{
		throw std::runtime_error("Failed to load shader source");	
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertexShader, fragmentShader;
	int success;
	char infoLog[512];

    /*
     * Create vertex shader object 
     *
     * glShaderSource sets sets source code in shader to source in vShaderCode
     * glCompileShader compiles the source code stored in shader
     *
     */
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);

	/* check to see if compilation was successful */	
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		throw std::runtime_error("Vertex shader compilation failed");
    }

    /*
     * Create fragment shader object 
     * 
     * glShaderSource sets source code in shader to source in fShaderCode
     * glCompileShader compiles the source code stored in shader
     *
     */
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);
	
	/* check to see if compilation was sucessful */
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		throw std::runtime_error("Fragment shader compilation failed");
    }
	
	/* after compiling the shaders, we must link them into a program */
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    /* check to see if linking was successful */
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
		throw std::runtime_error("Shader program linking failed");
    }

    /* delete shader objects (we don't need them anymore) */
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}	

void Shader::use()
{
	glUseProgram(ID);
}


void Shader::setInt(const std::string &name, int v0, int v1, int v2, int v3) const
{
	glUniform4i(glGetUniformLocation(ID, name.c_str()), v0, v1, v2, v3);
}

void Shader::setFloat(const std::string &name, float f0, float f1, float f2, float f3) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), f0, f1, f2, f3);
}

} // end namespace cpp_tetris
