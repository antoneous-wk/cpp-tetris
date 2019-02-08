#ifndef CPP_TETRIS_TEXTURE_HPP
#define CPP_TETRIS_TEXTURE_HPP

#include <glad/glad.h>

namespace cpp_tetris
{

class Texture2D
{
  public:
  Texture2D(int wrap_s, int wrap_t, int filterMin, int filterMax, int width, int height,
			int format, unsigned char* data); 

  void Generate();
  void Bind();

  private:
  unsigned ID;
  int Wrap_S;
  int Wrap_T;
  int Filter_min;
  int Filter_max;
  int Format;
  int Width;
  int Height; 
  unsigned char* Data;
  
};

} // namespace cpp_tetris

#endif // header guard
