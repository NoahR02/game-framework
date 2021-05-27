#ifndef RPG_VERTEXARRAY_H
#define RPG_VERTEXARRAY_H

#include <glad/glad.h>

class VertexArray {

private:
  unsigned int rendererID;

public:
  VertexArray();

  void enableAttribute(unsigned int attribute = 0);
  void disableAttribute(unsigned int attribute = 0);
  void describeAttributeLayout(unsigned int attribute = 0, int size = 3, GLenum type = GL_FLOAT, bool normalized = false, int stride = 0, int offset = 0);

  void bind();
  void unBind();

  ~VertexArray();

};


#endif //RPG_VERTEXARRAY_H
