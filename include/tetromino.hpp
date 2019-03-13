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

namespace cpp_tetris {

enum tetrominoType {
  tee, 
  saw,
  zee,
  stick,
  right,
  left,
  box,
  COUNT  // number of tetrominoTypes 
};

// each 16 bit hex number represents a tetromino orientation in 4x4 grid
// there are four blocks per tetromino grid, example:
// 0 1 0 0
// 1 1 0 0
// 0 1 0 0
// 0 0 0 0
static vector<vector<bitset<16>>> tetrominos = 
    // 0    // 90   // 180  // 270
  {{0x4640, 0x0E40, 0x4C40, 0x4E00},     // 'tee'
   {0x8C40, 0x6C00, 0x8C40, 0x6C00},     // 'saw'
   {0x4C80, 0xC600, 0x4C80, 0xC600},     // 'zee'
   {0x4444, 0x0F00, 0x4444, 0x0F00},     // 'stick'
   {0x44C0, 0x8E00, 0xC880, 0xE200},     // 'right'
   {0x88C0, 0xE800, 0xC440, 0x2E00},     // 'left'
   {0xCC00, 0xCC00, 0xCC00, 0xCC00}};    // 'box'

class Tetromino {
  public:
    Tetromino(unsigned tetromino);    
//  private:
    void setAttributes(unsigned tetromino);
    void resolveBlockCoordinates(unsigned orientation);
    void generateBlocks();
    vector<unsigned> blockCoordinates_;
    vector<bitset<16>> tetromino_;
    glm::vec2 tetrominoCoordinates_;
    glm::vec3 color_;
    vector<Block*> blocks_;
};

} // namespace cpp_tetris

#endif // header guard


