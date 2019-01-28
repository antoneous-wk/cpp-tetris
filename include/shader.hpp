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
	Shader(const char* vertexPath, const char* fragmentPath);
	
	void use();

	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;

	private:
	unsigned int ID;
};	
	
} // end namespace cpp_tetris

#endif // header guard
