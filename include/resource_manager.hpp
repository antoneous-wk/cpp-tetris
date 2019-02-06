#ifndef CPP_TETRIS_RESOURCE_MANAGER_HPP
#define CPP_TETRIS_RESOURCE_MANAGER_HPP

#include "shader.hpp"
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

	const string& getPath() const { return project_path; }
    Shader& getShader(string pname) { return *Shaders[pname]; } 
	string resolveProjectPath(const string argv);
    void loadShader(string, const char*, const char*);

  private:
    map<string, shared_ptr<Shader>> Shaders;	
    const string project_path;
};

} // namespace cpp_tetris

#endif // header guard
