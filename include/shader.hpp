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

using namespace std;

namespace cpp_tetris
{

class Shader
{
  public:
	Shader() = default;
    Shader(const char* vShaderCode, const char* fShaderCode);

	void compileProgram();	
    void useProgram();

    void setUniform1ui(const string& name, unsigned) const;
    void setUniform4i(const string& name, int, int, int, int) const;
    void setUniform4f(const string& name, float, float, float, float) const;
    void setUniform3f(const string& name, const glm::vec3&) const;
    void setUniformMatrix4f(const string& name, const glm::mat4&) const;

  private:
	void checkCompileErrors(unsigned name, bool is_shader, const string& error);

    unsigned ID;
	const char* vertexShaderCode;
	const char* fragmentShaderCode;
};	
	
} // namespace cpp_tetris

#endif // header guard
