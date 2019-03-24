#ifndef CPP_TETRIS_TETROMINO_HPP
#define CPP_TETRIS_TETROMINO_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <bitset>
#include <vector>
#include "block.hpp"

using std::vector;
using std::bitset;

// forward declarations
class Model;

namespace cpp_tetris {

enum tetrominoType {
  TEE,
  SAW,
  ZEE,
  STICK,
  RIGHT,
  LEFT,
  BOX,
  COUNT  // number of tetrominoTypes 
};

enum userInput {
  KEY_LEFT,
  KEY_RIGHT,
  KEY_UP,
  KEY_DOWN 
};

class Tetromino {
    friend class Model;
  public:
    Tetromino(tetrominoType shape, glm::vec3 color, Texture2D& sprite);    
    ~Tetromino();
    void update();
    void draw(SpriteRenderer& renderer);
    void rotate(float deltaTime);
    void moveX(userInput input, float deltaTime);
    void moveY(float deltaTime);
  private:
    void setOrientation(unsigned angle);
    void calculateBlockPosition();
    void updateBits();
    vector<bitset<12>> updateBits(bitset<16> orientation);
    void generateBlocks(Texture2D& sprite);
    bool detectCollisionY();
    bool detectCollisionX(userInput input);
    bool detectCollisionRotate(unsigned angle);
    void destroyBlocks(vector<unsigned> completeRows);

    // data members
    tetrominoType shape_;
    glm::vec3 color_;
    unsigned angle_;
    glm::vec2 position_;
    glm::vec2 velocity_;
    bitset<16> orientation_;

    vector<bitset<12>> bits_{0, 0, 0, 0};
    void calcBlockPosition();


    vector<unsigned> blockPosition_;
    vector<Block*> blocks_;
    bool isPlaced_;
    bool isDestroyed_;

    // static members
    const static vector<vector<bitset<16>>> tetrominos;
    static vector<bitset<12>> grid;

};

} // namespace cpp_tetris

#endif // header guard


