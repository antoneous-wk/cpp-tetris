#include "resource_manager.hpp"

/* STB_IMAGE_IMPLEMENTATION must be defined before including stb_image.h */
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace cpp_tetris
{

ResourceManager::ResourceManager(const std::string argv)
  : project_path{resolveProjectPath(argv)} { }

void ResourceManager::loadShader(const std::string& name, const char* vertexShaderPath,
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
  Shaders[name] = shader;
}	

void ResourceManager::loadTexture2D(std::string name, const char* texturePath, int wrap_S, 
									int wrap_T, int filterMin, int filterMax, int format)
{
  stbi_set_flip_vertically_on_load(true);
  int width, height, nrChannels;

  unsigned char *data{stbi_load((project_path + texturePath).c_str(), &width, &height,
    &nrChannels, 0)};

  if (data) {
    std::shared_ptr<Texture2D> texture{std::make_shared<Texture2D>(wrap_S, wrap_T, filterMin,
      filterMax, width, height, format, data)};
    texture->Generate();
    Textures2D[name] = texture;
    stbi_image_free(data);
  }
  else {
    stbi_image_free(data);
    throw std::runtime_error("Failed to load texture");
  }
}

/*
 * Resolves path of project root directory from main() argv[0].
 * Usage: Prepend the return value to the relative path of desired resource file.
 * Compatible with Unix filesystems.
 */
std::string ResourceManager::resolveProjectPath(const string& argv)
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
