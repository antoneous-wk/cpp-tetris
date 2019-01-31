#ifndef CPP_TETRIS_SHADER_HPP
#define CPP_TETRIS_SHADER_HPP

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace cpp_tetris
{

class Shader
{
	public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	
	void use();

	void setInt(const std::string &name, int, int, int, int) const;
	void setFloat(const std::string &name, float, float, float, float) const;

	private:
	unsigned int ID;
};	
	
} // namespace cpp_tetris

#endif // header guard
