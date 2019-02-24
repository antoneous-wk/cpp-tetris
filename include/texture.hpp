#ifndef CPP_TETRIS_TEXTURE_HPP
#define CPP_TETRIS_TEXTURE_HPP

#include <glad/glad.h>

/* forward declaration */
class ResourceManager;

namespace cpp_tetris {

class Texture2D {
  friend class ResourceManager;
	
  public:
    Texture2D();
    Texture2D(int wrap_s, int wrap_t, int filterMin, int filterMax, 
			  int width, int height, int format, unsigned char* data); 

    void bind();

  private:
    void generate();
    unsigned ID;
    int wrapS_;
    int wrapT_;
    int filterMin_;
    int filterMax_;
    int format_;
    int width_;
    int height_; 
    unsigned char* data_;
};

} // namespace cpp_tetris

#endif // header guard
