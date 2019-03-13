#ifndef CPP_TETRIS_TETROMINO_HPP
#define CPP_TETRIS_TETROMINO_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <bitset>
#include <vector>
#include "block.hpp"

using namespace std;

// foward declarations
class Model;

namespace cpp_tetris {

enum userInput {
  KEY_LEFT,
  KEY_RIGHT,
  KEY_UP,
  KEY_DOWN 
};

enum grid {
  X_OFFSET = 20,
  Y_OFFSET = 20,
  SPACING = 40
};

enum shape {
  TEE, 
  SAW,
  ZEE,
  STICK,
  RIGHT,
  LEFT,
  BOX,
  COUNT  // number of tetrominoTypes 
};

class Tetromino {
    friend class Model;
  public:
    Tetromino(unsigned tetromino, Texture2D& sprite);    
    ~Tetromino();
    void draw(SpriteRenderer& renderer);
    void moveX(userInput input, float deltaTime);
    void moveY(float deltaTime);
  private:
    void setAttributes(unsigned tetromino);
    void resolveRelativePosition(unsigned orientation);
    void resolveAbsolutePosition();
    void generateBlocks(Texture2D& sprite);
    vector<unsigned> blockPosition_;
    vector<bitset<16>> tetromino_;
    vector<Block*> blocks_;
    glm::vec2 tetrominoPosition_;
    glm::vec3 color_;
    glm::vec2 velocity_;
    bool isPlaced_;

    // static members
    static vector<vector<bitset<16>>> tetrominos;
};

} // namespace cpp_tetris

#endif // header guard


