#include "shader.hpp"

namespace cpp_tetris
{

Shader::Shader(const char* vShaderCode, const char* fShaderCode) 
  : vertexShaderCode{vShaderCode}, fragmentShaderCode{fShaderCode} { }

void Shader::compileProgram() 
{
  unsigned vertexShader, fragmentShader;

  /* create vertex shader object and compile */
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
  glCompileShader(vertexShader);

  /* check to see if compilation was successful */	
  error(vertexShader, true, "Vertex shader compilation failed.");

  /* create fragment shader object and compile */
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
  glCompileShader(fragmentShader);
	
  /* check to see if compilation was sucessful */
  error(fragmentShader, true, "Fragment shader compilation failed."); 
	
  /* after compiling the shaders, we must link them into a program */
  ID = glCreateProgram();
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);
  glLinkProgram(ID);

  /* check to see if linking was successful */
  error(ID, false, "Shader program linking failed."); 

  /* delete shader objects (we don't need them anymore) */
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}	

void Shader::error(unsigned name, bool is_shader, const char* error_message)
{
  int success;
  char infoLog[512];   

  /* check to see if shader compilation is sucessful */
  if(is_shader) {
  	glGetShaderiv(name, GL_COMPILE_STATUS, &success);
    if(!success) {
      glGetShaderInfoLog(name, 512, NULL, infoLog);
	  throw std::runtime_error(error_message);
    }
  }

  /* check to see if program linking was successful */ 
  else {
    glGetProgramiv(name, GL_LINK_STATUS, &success);
    if(!success) {
      glGetProgramInfoLog(name, 512, NULL, infoLog);
	  throw std::runtime_error(error_message);
    }
  }
}

void Shader::useProgram()
{
  glUseProgram(ID);
}

void Shader::setUniform4i(const std::string &name, int v0, int v1, int v2, int v3) const
{
  glUniform4i(glGetUniformLocation(ID, name.c_str()), v0, v1, v2, v3);
}

void Shader::setUniform4f(const std::string &name, float f0, float f1, float f2, 
						  float f3) const
{
  glUniform4f(glGetUniformLocation(ID, name.c_str()), f0, f1, f2, f3);
}

void Shader::setUniformMatrix4fv(const std::string &name, const glm::mat4& mat) const
{
  glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
					 glm::value_ptr(mat));
}  

} // end namespace cpp_tetris
