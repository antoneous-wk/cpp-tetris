#ifndef CPP_TETRIS_SHADER_HPP
#define CPP_TETRIS_SHADER_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

namespace cpp_tetris
{

class Shader
{
  public:
	Shader() = default;
    Shader(const char* vShaderCode, const char* fShaderCode);

	void compileProgram();	
    void useProgram();

    void setUniform4i(const std::string& name, int, int, int, int) const;
    void setUniform4f(const std::string& name, float, float, float, float) const;     void setUniform3f(const std::string& name, const glm::vec3&) const;
    void setUniformMatrix4f(const std::string& name, const glm::mat4&) const;

  private:
	void checkCompileErrors(unsigned name, bool is_shader, const std::string& error);

    unsigned ID;
	const char* vertexShaderCode;
	const char* fragmentShaderCode;
};	
	
} // namespace cpp_tetris

#endif // header guard
