#ifndef RPG_ELEMENTBUFFER_H
#define RPG_ELEMENTBUFFER_H

#include <glad/glad.h>
#include <vector>

class ElementBuffer {

private:
  unsigned int rendererID;

public:
  ElementBuffer();

  void fillBuffer(std::vector<unsigned int>& data, GLenum usage = GL_STATIC_DRAW);
  void fillBuffer(long size, GLenum usage);
  void fillBufferSubData(std::vector<unsigned int>& data, int offset = 0);

  void bind();
  void unBind();

  ~ElementBuffer();

};


#endif //RPG_ELEMENTBUFFER_H
