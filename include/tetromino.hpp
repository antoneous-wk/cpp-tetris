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

// foward declarations
class Model;

namespace cpp_tetris {

enum userInput {
  KEY_LEFT,
  KEY_RIGHT,
  KEY_UP,
  KEY_DOWN 
};

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

class Tetromino {
    friend class Model;
  public:
    Tetromino(unsigned tetromino, Texture2D& sprite);    
    ~Tetromino();
    void update();
    void draw(SpriteRenderer& renderer);
    void rotate(float deltaTime);
    void moveX(userInput input, float deltaTime);
    void moveY(float deltaTime);
  private:
    tetrominoType setShape(unsigned shape);
    glm::vec3 getColor();


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

    bitset<16> orientation_;
    vector<bitset<12>> bits_{0, 0, 0, 0};



    vector<unsigned> blockPosition_;
    vector<Block*> blocks_;
    glm::vec2 tetrominoPosition_;
    glm::vec2 velocity_;
    unsigned angle_;
    bool isPlaced_;
    bool isDestroyed_;

    // static members
    const static vector<vector<bitset<16>>> tetrominos;
    static vector<bitset<12>> grid;

};

} // namespace cpp_tetris

#endif // header guard


