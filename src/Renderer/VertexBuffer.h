#ifndef RPG_VERTEXBUFFER_H
#define RPG_VERTEXBUFFER_H


#include <glad/glad.h>
#include <vector>

class VertexBuffer {

private:
  unsigned int rendererID;

public:
  VertexBuffer();

  void fillBuffer(std::vector<float>& data, GLenum usage = GL_STATIC_DRAW);
  void bind();
  void unBind();

  ~VertexBuffer();

};


#endif //RPG_VERTEXBUFFER_H
