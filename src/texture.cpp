#include "texture.hpp"

namespace cpp_tetris {

Texture2D::Texture2D()
  : wrapS_{GL_REPEAT}, wrapT_{GL_REPEAT}, filterMin_{GL_LINEAR},
    filterMax_{GL_LINEAR}, width_{0}, height_{0}, format_{GL_RGBA} { }

Texture2D::Texture2D(int wrapS, int wrapT, int filterMin, int filterMax, 
					 int width, int height, int format, unsigned char* data)
  : wrapS_{wrapS}, wrapT_{wrapT}, filterMin_{filterMin}, filterMax_{filterMax},
    width_{width}, height_{height}, format_{format}, data_{data} { }

void Texture2D::generate() {
  glGenTextures(1, &(this->ID));
  this->bind();
   
  // set the texture wrapping/filtering options (for currently bound texture) 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS_);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT_);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin_);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMax_);
  
  glTexImage2D(GL_TEXTURE_2D, 0, this->format_, this->width_, this->height_, 0, 
			   this->format_, GL_UNSIGNED_BYTE, this->data_);
  glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture2D::bind() {
  glBindTexture(GL_TEXTURE_2D, this->ID);
}

} // namespace cpp_tetris
