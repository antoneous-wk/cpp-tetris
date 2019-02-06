#include "resource_manager.hpp"

namespace cpp_tetris
{

ResourceManager::ResourceManager(const std::string argv)
  : project_path{resolveProjectPath(argv)} { }

void ResourceManager::loadShader(std::string pname, const char* vertexShaderPath,
								 const char* fragmentShaderPath) 
{ 
  std::string vertexShaderCode;
  std::string fragmentShaderCode;

  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    vShaderFile.open(project_path + vertexShaderPath);
    fShaderFile.open(project_path + fragmentShaderPath);

    std::stringstream vShaderStream, fShaderStream;

    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vShaderFile.close();
    fShaderFile.close();

    vertexShaderCode = vShaderStream.str();
    fragmentShaderCode = fShaderStream.str();
    }
    catch(const std::ifstream::failure& e) {
      throw std::runtime_error("Failed to load shader source");
    }

  const char* vShaderCode{vertexShaderCode.c_str()};
  const char* fShaderCode{fragmentShaderCode.c_str()};

  std::shared_ptr<Shader> shader{std::make_shared<Shader>(vShaderCode, fShaderCode)};
  shader->compileProgram();
  Shaders[pname] = shader;
}	

/*
 * Resolves path of project root directory from main() argv[0].
 * Usage: Prepend the return value to the relative path of desired resource file.
 * Compatible with Unix filesystems.
 */
std::string ResourceManager::resolveProjectPath(const std::string argv)
{
  /* if we are in /build/src directory */
  if (argv == "./demo") return "../../";
  /* if we are in build directory */
  if (argv == "./src/demo") return "../"; 
  /* if we are in project directory */
  if (argv == "./build/src/demo") return "./";
  /* if we are above or nested above project directory */
  std::string project{"cpp-tetris"};
  std::string path{argv};
  std::size_t pos{argv.find(project)};
  if(pos != std::string::npos) {
        path.erase((path.begin()+pos+project.length()), path.end());
        return path + "/";
  }
  /* if we are below or nested below build directory */
  else if(argv[1] == '.') {
  pos = argv.rfind("../");
  path.erase(path.begin()+pos+3, path.end());
  std::cout << path + ".." << std::endl;
  return path + "../";
  }

  throw std::runtime_error("Failed to resolve project path.");
}

} // namespace cpp_tetris
