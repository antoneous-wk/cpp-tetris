#ifndef CPP_TETRIS_GAME_OBJECT_HPP
#define CPP_TETRIS_GAME_OBJECT_HPP

#include <memory>

using namespace std;

namespace cpp_tetris
{

class GameObject
{
  public:
    GameObject(ResourceManager& rm) : resourceManager{rm} { } 

    virtual void Init() = 0;
    virtual const unsigned& getVAO() const { return VAO; }
    virtual const unsigned& getVBO() const { return VBO; }
    
  protected:
    ResourceManager& resourceManager;
	std::string shaderName;
	std::string textureName;
    unsigned VAO;
    unsigned VBO;
};

} // namespace cpp_tetris

#endif // header guard
