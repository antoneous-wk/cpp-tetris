#ifndef CPP_TETRIS_RESOURCE_MANAGER_HPP
#define CPP_TETRIS_RESOURCE_MANAGER_HPP

#include "shader.hpp"
#include "texture.hpp"
#include <map>
#include <string>
#include <memory>

using namespace std;

namespace cpp_tetris
{

class ResourceManager
{
  public:
    ResourceManager(const string argv);    
	
	/* get project path */
	const string& getPath() const { return project_path; }
    Shader& getShader(const string& name) { return *Shaders[name]; } 

    void loadShader(const string& name, const char* vertexShaderPath, 
					const char* fragmentShaderPath);

    void loadTexture2D(string name, const char* texturePath, int wrap_S, int wrap_T,
				       int filterMin, int filterMax, int format);

  private:
	string resolveProjectPath(const string& argv);
    map<string, shared_ptr<Shader>> Shaders;	
    map<string, shared_ptr<Texture2D>> Textures2D;
    const string project_path;
};

} // namespace cpp_tetris

#endif // header guard
