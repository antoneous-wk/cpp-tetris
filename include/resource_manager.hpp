#ifndef CPP_TETRIS_RESOURCE_MANAGER_HPP
#define CPP_TETRIS_RESOURCE_MANAGER_HPP

#include "shader.hpp"
#include "texture.hpp"
#include <map>
#include <string>
#include <memory>
#include <iostream>

using namespace std;

namespace cpp_tetris
{

class ResourceManager
{
  public:
    ResourceManager(const string argv);    
    ~ResourceManager();
	
    // get project path 
    const string& getPath() const { return project_path; }
    Shader& getShader(const string& name) { return *Shaders[name]; } 
    Texture2D& getTexture2D(const string& name) { return *Textures2D[name]; }

    void loadShader(const string& name, const char* vertexShaderPath, 
 				    const char* fragmentShaderPath);

    void loadTexture2D(const string& name, const char* texturePath, 
					   int wrapS, int wrapT, int filterMin, int filterMax, 
					   int format);

  private:
    string resolveProjectPath(const string& argv);
    map<string, Shader*> Shaders;
    map<string, Texture2D*> Textures2D;
    const string project_path;
};

} // namespace cpp_tetris

#endif // header guard
