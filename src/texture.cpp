#include "texture.hpp"

namespace cpp_tetris
{

Texture2D::Texture2D(int wrap_s, int wrap_t, int filterMin, int filterMax, int width,
                     int height, int format, unsigned char* data)
  : Wrap_S{wrap_s}, Wrap_T{wrap_t}, Filter_min{filterMin}, Filter_max{filterMax},
    Width{width}, Height{height}, Format{format}, Data{data} { }

void Texture2D::Generate()
{
  glGenTextures(1, &(this->ID));

  this->Bind();
   
   /* set the texture wrapping/filtering options (for currently bound texture) */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_min);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_max);
  
  glTexImage2D(GL_TEXTURE_2D, 0, this->Format, this->Width, this->Height, 0, this->Format,
    GL_UNSIGNED_BYTE, this->Data);
  glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture2D::Bind()
{
  glBindTexture(GL_TEXTURE_2D, this->ID);
}

} // namespace cpp_tetris
