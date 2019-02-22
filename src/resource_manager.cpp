#include "resource_manager.hpp"

// STB_IMAGE_IMPLEMENTATION must be defined before including stb_image.h 
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace cpp_tetris {

ResourceManager::ResourceManager(const string argv)
  : project_path{resolveProjectPath(argv)} { }

ResourceManager::~ResourceManager() {
  // when we fetch an element from a map, we get object of type 'pair'
  // each element has data members 'first' and 'second' 
  // 'first' is key, 'second' is value
  for(auto &shader : Shaders) {
    if(shader.second) { 
      delete shader.second;
      shader.second = nullptr;
    }
  }
  for(auto &texture : Textures2D) {
    if(texture.second) {
      delete texture.second;
      texture.second = nullptr;
    }
   }
}

void ResourceManager::loadShader(const string& name, 
								 const char* vertexShaderPath,
								 const char* fragmentShaderPath) { 
  string vertexShaderCode;
  string fragmentShaderCode;

  ifstream vShaderFile;
  ifstream fShaderFile;

  vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
  fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

  try {
    vShaderFile.open(project_path + vertexShaderPath);
    fShaderFile.open(project_path + fragmentShaderPath);

    stringstream vShaderStream, fShaderStream;

    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vShaderFile.close();
    fShaderFile.close();

    vertexShaderCode = vShaderStream.str();
    fragmentShaderCode = fShaderStream.str();
    }
    catch(const ifstream::failure& e) {
      throw runtime_error("Failed to load shader source");
    }

  const char* vShaderCode{vertexShaderCode.c_str()};
  const char* fShaderCode{fragmentShaderCode.c_str()};

  Shader* shader{new Shader{vShaderCode, fShaderCode}};
  shader->compileProgram();
  Shaders[name] = shader;
}	

void ResourceManager::loadTexture2D(const string& name, 
									const char* texturePath, 
									int wrapS, int wrapT, int filterMin, 
									int filterMax, int format) {

  stbi_set_flip_vertically_on_load(true);
  int width, height, nrChannels;
  unsigned char *data{stbi_load((project_path + texturePath).c_str(), 
    &width, &height, &nrChannels, 0)};

  if (data) {
    Texture2D* texture{new Texture2D{wrapS, wrapT, filterMin, filterMax, 
      width, height,  format, data}};

    texture->generate();
    Textures2D[name] = texture;
    stbi_image_free(data);
  }
  else {
    stbi_image_free(data);
    throw runtime_error("Failed to load texture");
  }
}

/*
 * Resolves path of project root directory from main() argv[0].
 * Usage: Prepend the return value to the relative path of desired resource file.
 * Compatible with Unix filesystems.
 */
string ResourceManager::resolveProjectPath(const string& argv)
{
  // if we are in /build/src directory 
  if (argv == "./demo") return "../../";
  // if we are in build directory 
  if (argv == "./src/demo") return "../"; 
  // if we are in project directory 
  if (argv == "./build/src/demo") return "./";
  // if we are above or nested above project directory 
  string project{"cpp-tetris"};
  string path{argv};
  size_t pos{argv.find(project)};
  if(pos != string::npos) {
        path.erase((path.begin()+pos+project.length()), path.end());
        return path + "/";
  }
  // if we are below or nested below build directory 
  else if(argv[1] == '.') {
  pos = argv.rfind("../");
  path.erase(path.begin()+pos+3, path.end());
  cout << path + ".." << endl;
  return path + "../";
  }

  throw runtime_error("Failed to resolve project path.");
}

} // namespace cpp_tetris
