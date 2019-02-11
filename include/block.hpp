#ifndef CPP_TETRIS_BLOCK_HPP
#define CPP_TETRIS_BLOCK_HPP

using namespace std;

namespace cpp_tetris
{

class Block : public GameObject
{
  public:
    Block(ResourceManager& rm) : GameObject{rm} { } 
    virtual void Init() override;

  private:

};

void Block::Init() 
{
  float vertices[]
  { // position         // colors           // texture coords
    0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
    0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
   -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f,

    0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
   -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
   -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f
  };

  //unsigned int VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  /* VAO must be bound before VBO and EBO */
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  /* creates new data store (in graphics card memory) for currently bound buffer object */
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  /* specify how OpenGL should interpret vertex attribute data and enable the attribute */
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
    (void*) (3 * sizeof(float)));

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  /*
   * Unbind VAO and VBO
   * The VAO stores the state since it was first bound.
   * We are allowed to unbind the VBO because glVertexAttribPointer registered the
   * VBO as the VAO's bound vertex buffer object.
   */
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

} // namespace cpp_tetris

#endif // header guard
